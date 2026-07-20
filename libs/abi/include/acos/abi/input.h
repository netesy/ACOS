#pragma once
#include <acos/types.h>

namespace acos::abi {

enum class InputType {
    Keyboard,
    Mouse,
    Touch,
    Joystick
};

enum class VirtualKey : u32 {
    None = 0,
    A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Escape,
    Enter,
    Space,
    Backspace,
    Tab,
    LShift, RShift,
    LCtrl, RCtrl,
    LAlt, RAlt,
    Up, Down, Left, Right,
    Home, End, PageUp, PageDown,
    Insert, Delete,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    Minus, Equals, LBracket, RBracket, Semicolon, Quote, Backtick, Backslash, Comma, Period, Slash,
    CapsLock, NumLock, ScrollLock
};

namespace ModifierFlags {
    static constexpr u32 Shift = 1 << 0;
    static constexpr u32 Ctrl  = 1 << 1;
    static constexpr u32 Alt   = 1 << 2;
}

struct InputEvent {
    InputType type;
    u32 code;
    u32 value;
    u32 flags;
};

} // namespace acos::abi
