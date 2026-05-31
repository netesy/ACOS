#pragma once
#include <acos/types.h>

namespace acos::display {

using WindowId = u64;

enum class WindowState {
    Normal,
    Minimized,
    Maximized,
    Hidden
};

namespace WindowFlags {
    static constexpr u32 None        = 0;
    static constexpr u32 Frameless   = 1 << 0;
    static constexpr u32 Transparent = 1 << 1;
    static constexpr u32 AlwaysOnTop = 1 << 2;
}

class Window {
public:
    Window(WindowId id, u64 owner_pid, u32 x, u32 y, u32 width, u32 height);

    WindowId id() const { return m_id; }
    u64 owner_pid() const { return m_owner_pid; }

    u32 x() const { return m_x; }
    u32 y() const { return m_y; }
    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    u32 z_order() const { return m_z_order; }

    void set_position(u32 x, u32 y) { m_x = x; m_y = y; }
    void set_size(u32 w, u32 h) { m_width = w; m_height = h; }
    void set_z_order(u32 z) { m_z_order = z; }

    WindowState state() const { return m_state; }
    void set_state(WindowState s) { m_state = s; }

    bool is_visible() const { return m_state != WindowState::Hidden; }
    bool is_focused() const { return m_focused; }
    void set_focused(bool focused) { m_focused = focused; }

    u64 surface_id() const { return m_surface_id; }
    void set_surface_id(u64 id) { m_surface_id = id; }

private:
    WindowId m_id;
    u64 m_owner_pid;
    u32 m_x, m_y;
    u32 m_width, m_height;
    u32 m_z_order;
    WindowState m_state;
    u32 m_flags;
    bool m_focused;
    u64 m_surface_id;
};

} // namespace acos::display
