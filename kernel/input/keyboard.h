#pragma once
#include <kernel/input/input_device.h>

namespace acos::input {

class KeyboardDevice : public InputDevice {
public:
    virtual ~KeyboardDevice() = default;
    InputType type() const override { return InputType::Keyboard; }

    virtual void handle_scancode(u8 scancode) = 0;
};

} // namespace acos::input
