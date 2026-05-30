#pragma once
#include <acos/types.h>

namespace acos::input {

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

class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool initialize() = 0;
    virtual InputType type() const = 0;
};

} // namespace acos::input
