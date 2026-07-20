#pragma once
#include <acos/types.h>
#include <acos/abi/input.h>

namespace acos::input {

class KeyboardManager {
public:
    static void init();
    static void handle_scancode(u8 scancode);

    static bool shift_pressed() { return m_shift; }
    static bool ctrl_pressed() { return m_ctrl; }
    static bool alt_pressed() { return m_alt; }

private:
    static bool m_shift;
    static bool m_ctrl;
    static bool m_alt;
};

} // namespace acos::input
