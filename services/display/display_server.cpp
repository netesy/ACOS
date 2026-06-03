#include "display_server.h"
#include <kernel/graphics/graphics_manager.h>
#include <kernel/memory/heap.h>
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
    if (m_graphics_channel.receive(msg, false)) {
        handle_request(msg);
    }
    if (m_compositor) {
        m_compositor->compose();
    }
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

void DisplayServer::handle_request(const acos::ipc::Message& msg) {
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

} // namespace acos::display
