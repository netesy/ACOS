#include "display_server.h"
#include <kernel/graphics/graphics_manager.h>
#include <kernel/memory/heap.h>
#include <kernel/hal/serial.h>
#include <kernel/hal/console.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::display {

DisplayServer::DisplayServer()
    : m_window_count(0), m_last_window_id(0), m_compositor(nullptr), m_running(false) {
    for (usize i = 0; i < MAX_WINDOWS; i++) m_windows[i] = nullptr;
}

bool DisplayServer::initialize() {
    acos::graphics::DisplayDevice* display = acos::graphics::GraphicsManager::primary_display();
    if (!display) return false;

    acos::graphics::Framebuffer* fb = display->get_framebuffer();
    if (!fb) return false;

    m_compositor = (Compositor*)acos::memory::kmalloc(sizeof(Compositor));
    if (!m_compositor) return false;
    new (m_compositor) Compositor(fb, &m_surface_manager);

    m_compositor->set_windows(m_windows, 0);
    m_input_router.set_windows(m_windows, 0);

    return true;
}

void DisplayServer::run() {
    m_running = true;
    acos::hal::console_print("Display Server: Initialized and running\n");

    while (m_running) {
        run_tick();
    }
}

void DisplayServer::run_tick() {
    acos::ipc::Message msg;
    if (m_command_channel.receive(msg, false)) {
        handle_request(msg);
    }
    if (m_compositor) {
        m_compositor->compose();
    }
}

// Threaded run loop: process all pending IPC commands, then compose.
// Halts when idle to avoid burning CPU in QEMU/TCG.
void DisplayServer::run_loop() {
    m_running = true;
    acos::hal::serial_print("Display Server: run_loop started on DS thread\n");

    while (m_running) {
        // Drain all pending commands (non-blocking)
        acos::ipc::Message msg;
        while (m_command_channel.receive(msg, false)) {
            handle_request(msg);
        }

        // Compose if there's damage or always-dirty desktop
        if (m_compositor) {
            m_compositor->compose();
        }

        // Yield CPU until next event (IPC send wakes us via scheduler)
        __asm__ volatile("hlt");
    }
}

bool DisplayServer::send_command(const DisplayMsg& cmd, u64 sender_pid) {
    acos::ipc::Message msg;
    msg.sender = sender_pid;
    msg.receiver = 0; // display server
    msg.type = static_cast<u32>(cmd.type);
    msg.flags = 0;
    msg.size = sizeof(DisplayMsg);
    msg.payload = const_cast<DisplayMsg*>(&cmd);
    msg.cap_handle = 0;
    return m_command_channel.send(msg);
}

void DisplayServer::set_desktop_draw(Compositor::DesktopDrawFn fn) {
    if (m_compositor) {
        m_compositor->set_desktop_draw(fn);
        m_compositor->mark_always_dirty();
    }
}

acos::graphics::Renderer* DisplayServer::renderer() {
    return m_compositor ? m_compositor->renderer() : nullptr;
}

void DisplayServer::add_window(Window* win) {
    if (!win || m_window_count >= MAX_WINDOWS) return;
    m_windows[m_window_count++] = win;
    m_compositor->set_windows(m_windows, m_window_count);
    m_input_router.set_windows(m_windows, m_window_count);
    m_compositor->mark_dirty(win->x(), win->y(), win->width(), win->height());
}

void DisplayServer::mark_window_dirty(Window* win) {
    if (!win || !m_compositor) return;
    m_compositor->mark_dirty(win->x(), win->y(), win->width(), win->height());
}

void DisplayServer::handle_request(const acos::ipc::Message& msg) {
    if (msg.size >= sizeof(DisplayMsg) && msg.payload) {
        handle_display_msg(*static_cast<const DisplayMsg*>(msg.payload), msg.sender);
        return;
    }

    // Legacy GraphicsRequest path (backward compat)
    if (msg.size < sizeof(GraphicsRequest)) return;

    GraphicsRequest* req = (GraphicsRequest*)msg.payload;

    switch (req->type) {
        case GraphicsRequestType::CreateWindow: {
            if (m_window_count >= MAX_WINDOWS) break;

            WindowId id = next_window_id();
            Window* win = (Window*)acos::memory::kmalloc(sizeof(Window));
            if (!win) break;
            new (win) Window(id, msg.sender, req->create_window.x, req->create_window.y,
                             req->create_window.width, req->create_window.height);

            Surface* surface = m_surface_manager.create_surface(msg.sender, req->create_window.width, req->create_window.height);
            if (surface) {
                win->set_surface_id(surface->id);
            }

            m_windows[m_window_count++] = win;
            m_compositor->set_windows(m_windows, m_window_count);
            m_input_router.set_windows(m_windows, m_window_count);

            m_compositor->mark_dirty(win->x(), win->y(), win->width(), win->height());
            break;
        }
        case GraphicsRequestType::PresentSurface: {
            for (usize i = 0; i < m_window_count; i++) {
                if (m_windows[i]->id() == req->present.window_id && m_windows[i]->owner_pid() == msg.sender) {
                    m_surface_manager.swap_buffers(m_windows[i]->surface_id());
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    break;
                }
            }
            break;
        }
        default:
            break;
    }
}

void DisplayServer::handle_display_msg(const DisplayMsg& cmd, u64 sender_pid) {
    switch (cmd.type) {
        case DisplayMsgType::CreateWindow: {
            if (m_window_count >= MAX_WINDOWS) break;

            WindowId id = next_window_id();
            Window* win = (Window*)acos::memory::kmalloc(sizeof(Window));
            if (!win) break;
            new (win) Window(id, sender_pid,
                             cmd.create_window.x, cmd.create_window.y,
                             cmd.create_window.width, cmd.create_window.height);

            Surface* surface = m_surface_manager.create_surface(
                sender_pid, cmd.create_window.width, cmd.create_window.height);
            if (surface) {
                win->set_surface_id(surface->id);
            }

            m_windows[m_window_count++] = win;
            m_compositor->set_windows(m_windows, m_window_count);
            m_input_router.set_windows(m_windows, m_window_count);
            m_compositor->mark_dirty(win->x(), win->y(), win->width(), win->height());
            break;
        }

        case DisplayMsgType::DestroyWindow: {
            for (usize i = 0; i < m_window_count; i++) {
                if (m_windows[i]->id() == cmd.destroy_window.window_id &&
                    m_windows[i]->owner_pid() == sender_pid) {
                    // Mark region dirty before removing
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    // Shift remaining windows
                    for (usize j = i; j < m_window_count - 1; j++) {
                        m_windows[j] = m_windows[j + 1];
                    }
                    m_window_count--;
                    m_windows[m_window_count] = nullptr;
                    m_compositor->set_windows(m_windows, m_window_count);
                    m_input_router.set_windows(m_windows, m_window_count);
                    break;
                }
            }
            break;
        }

        case DisplayMsgType::MoveWindow: {
            for (usize i = 0; i < m_window_count; i++) {
                if (m_windows[i]->id() == cmd.move_window.window_id) {
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    m_windows[i]->set_position(cmd.move_window.x, cmd.move_window.y);
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    break;
                }
            }
            break;
        }

        case DisplayMsgType::ResizeWindow: {
            for (usize i = 0; i < m_window_count; i++) {
                if (m_windows[i]->id() == cmd.resize_window.window_id) {
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    m_windows[i]->set_size(cmd.resize_window.width, cmd.resize_window.height);
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    break;
                }
            }
            break;
        }

        case DisplayMsgType::PresentSurface: {
            for (usize i = 0; i < m_window_count; i++) {
                if (m_windows[i]->id() == cmd.present.window_id) {
                    m_surface_manager.swap_buffers(m_windows[i]->surface_id());
                    m_compositor->mark_dirty(m_windows[i]->x(), m_windows[i]->y(),
                                             m_windows[i]->width(), m_windows[i]->height());
                    break;
                }
            }
            break;
        }

        case DisplayMsgType::DamageNotify: {
            // Just trigger recomposition
            if (m_compositor) {
                m_compositor->mark_dirty(0, 0, 1, 1);
            }
            break;
        }

        case DisplayMsgType::TerminalText: {
            // Forward to the terminal window if it exists
            // (handled by TerminalWindow's own IPC listener in the future;
            //  for now the terminal writes directly to its back buffer)
            break;
        }
    }
}

} // namespace acos::display
