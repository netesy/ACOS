#include "input_router.h"
#include <kernel/ipc/channel.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/input/input_manager.h>

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
            // Send keyboard event to focused window owner via IPC
            // For now, this is a placeholder - full IPC integration needed
            (void)event;
        }
    } else if (event.type == acos::input::InputType::Mouse) {
        // Parse mouse event
        // Extract coordinates and button state from event
        // For now, use simplified approach
        u32 x = (event.code >> 16) & 0xFFFF;  // Extract x from code
        u32 y = event.code & 0xFFFF;           // Extract y from code
        bool pressed = (event.value & 0x01) != 0; // Button 1 pressed
        
        // Update mouse position and find window under cursor
        update_mouse(x, y, pressed);
        
        // Send mouse event to window under cursor
        if (m_mouse_over_window) {
            // For now, this is a placeholder - full IPC integration needed
            (void)event;
        }
    }
}

} // namespace acos::display
