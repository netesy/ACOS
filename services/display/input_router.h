#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>
#include "window.h"

namespace acos::display {

class InputRouter {
public:
    InputRouter();

    void route_event(const acos::input::InputEvent& event);

    void set_focus(Window* window);
    Window* focused_window() const { return m_focused_window; }

    void update_mouse(u32 x, u32 y, bool pressed);

    // To be called by the DisplayServer to provide the list of windows
    void set_windows(Window** windows, usize count);

private:
    Window* find_window_at(u32 x, u32 y);

    Window* m_focused_window;
    Window* m_mouse_over_window;

    u32 m_mouse_x;
    u32 m_mouse_y;
    bool m_mouse_pressed;

    Window** m_windows;
    usize m_window_count;
};

} // namespace acos::display
