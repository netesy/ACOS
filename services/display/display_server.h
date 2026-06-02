#pragma once
#include <acos/types.h>
#include <kernel/ipc/channel.h>
#include "window.h"
#include "surface_manager.h"
#include "compositor.h"
#include "input_router.h"

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
    void run();
    void run_tick();

    // IPC Channels as requested
    acos::ipc::Channel* graphics_channel() { return &m_graphics_channel; }
    acos::ipc::Channel* window_channel() { return &m_window_channel; }
    acos::ipc::Channel* surface_channel() { return &m_surface_channel; }

private:
    void handle_request(const acos::ipc::Message& msg);

    WindowId next_window_id() { return ++m_last_window_id; }

    static constexpr usize MAX_WINDOWS = 128;
    Window* m_windows[MAX_WINDOWS];
    usize m_window_count;
    WindowId m_last_window_id;

    SurfaceManager m_surface_manager;
    Compositor* m_compositor;
    InputRouter m_input_router;

    acos::ipc::Channel m_graphics_channel;
    acos::ipc::Channel m_window_channel;
    acos::ipc::Channel m_surface_channel;

    bool m_running;
};

} // namespace acos::display
