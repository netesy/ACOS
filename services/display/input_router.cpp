#include "input_router.h"

namespace acos::display {

InputRouter::InputRouter()
    : m_focused_window(nullptr), m_mouse_over_window(nullptr),
      m_mouse_x(0), m_mouse_y(0), m_mouse_pressed(false),
      m_windows(nullptr), m_window_count(0) {}

void InputRouter::set_windows(Window** windows, usize count) {
    m_windows = windows;
    m_window_count = count;
}

void InputRouter::set_focus(Window* window) {
    if (m_focused_window) {
        m_focused_window->set_focused(false);
    }
    m_focused_window = window;
    if (m_focused_window) {
        m_focused_window->set_focused(true);
    }
}

void InputRouter::update_mouse(u32 x, u32 y, bool pressed) {
    m_mouse_x = x;
    m_mouse_y = y;
    m_mouse_pressed = pressed;

    m_mouse_over_window = find_window_at(x, y);

    if (pressed && m_mouse_over_window) {
        set_focus(m_mouse_over_window);
    }
}

Window* InputRouter::find_window_at(u32 x, u32 y) {
    // Iterate windows in reverse Z-order (top to bottom)
    for (int i = (int)m_window_count - 1; i >= 0; i--) {
        Window* win = m_windows[i];
        if (!win || !win->is_visible()) continue;

        if (x >= win->x() && x < win->x() + win->width() &&
            y >= win->y() && y < win->y() + win->height()) {
            return win;
        }
    }
    return nullptr;
}

void InputRouter::route_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Keyboard) {
        if (m_focused_window) {
            // In a real implementation, we would send an IPC message to the owner_pid
        }
    } else if (event.type == acos::input::InputType::Mouse) {
        // Assume event.code is X/Y or buttons
        // Logic to update_mouse and then route...
    }
}

} // namespace acos::display
