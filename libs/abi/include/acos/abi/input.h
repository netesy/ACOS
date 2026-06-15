#pragma once
#include <acos/types.h>

namespace acos::abi {

enum class InputType {
    Keyboard,
    Mouse,
    Touch,
    Joystick
};

struct InputEvent {
    InputType type;
    u32 code;
    u32 value;
    u32 flags;
};

} // namespace acos::abi
