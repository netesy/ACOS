#pragma once
#include <acos/types.h>
#include <acos/abi/input.h>

namespace acos::input {

class MouseManager {
public:
    static void init();
    static void handle_movement(i32 dx, i32 dy);
    static void handle_button(u32 button, bool pressed);

    static i32 x() { return m_x; }
    static i32 y() { return m_y; }
    static u32 buttons() { return m_buttons; }

private:
    static i32 m_x;
    static i32 m_y;
    static u32 m_buttons;
};

} // namespace acos::input
