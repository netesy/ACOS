#pragma once
#include <acos/types.h>
#include <acos/ipc.h>
#include "window.h"
#include "surface_manager.h"
#include "compositor.h"
#include "input_router.h"
#include "display_protocol.h"

namespace acos::display {

enum class GraphicsRequestType : u32 {
    CreateWindow = 1,
    DestroyWindow = 2,
    MoveWindow = 3,
    ResizeWindow = 4,
    CreateSurface = 5,
    PresentSurface = 6,
    RegisterClient = 7
};

struct GraphicsRequest {
    GraphicsRequestType type;
    union {
        struct {
            u32 x, y, width, height;
        } create_window;
        struct {
            u64 window_id;
        } destroy_window;
        struct {
            u64 window_id;
            u32 x, y;
        } move_window;
        struct {
            u64 window_id;
            u32 width, height;
        } resize_window;
        struct {
            u64 window_id;
        } present;
    };
};

class DisplayServer {
public:
    DisplayServer();
    bool initialize();

    /// Legacy single-tick: drain one message + compose.
    /// Kept for backward compat; prefer run_loop().
    void run();
    void run_tick();

    /// Threaded run loop: process IPC commands + compose.
    /// Runs forever; meant to be called from a dedicated DS thread.
    void run_loop();

    /// Send a command to the DS command channel.
    /// Used by clients (TerminalWindow, DesktopShell, apps).
    bool send_command(const DisplayMsg& cmd, u64 sender_pid = 0);

    // IPC Channels
    acos::ipc::Channel* command_channel() { return &m_command_channel; }
    acos::ipc::Channel* graphics_channel() { return &m_command_channel; }
    acos::ipc::Channel* window_channel() { return &m_command_channel; }
    acos::ipc::Channel* surface_channel() { return &m_command_channel; }

    // Desktop background rendering
    void set_desktop_draw(Compositor::DesktopDrawFn fn);
    acos::graphics::Renderer* renderer();

    // Direct window creation helpers (for kernel-linked services)
    SurfaceManager& surface_manager_ref() { return m_surface_manager; }
    void add_window(Window* win);
    void mark_window_dirty(Window* win);

private:
    void handle_request(const acos::ipc::Message& msg);
    void handle_display_msg(const DisplayMsg& cmd, u64 sender_pid);

    WindowId next_window_id() { return ++m_last_window_id; }

    static constexpr usize MAX_WINDOWS = 128;
    Window* m_windows[MAX_WINDOWS];
    usize m_window_count;
    WindowId m_last_window_id;

    SurfaceManager m_surface_manager;
    Compositor* m_compositor;
    InputRouter m_input_router;

    // Unified command channel: all clients send DisplayMsg here.
    acos::ipc::Channel m_command_channel;

    bool m_running;
};

} // namespace acos::display
