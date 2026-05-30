#pragma once
#include <kernel/input/input_device.h>

namespace acos::input {

class MouseDevice : public InputDevice {
public:
    virtual ~MouseDevice() = default;
    InputType type() const override { return InputType::Mouse; }

    virtual void handle_movement(i32 dx, i32 dy) = 0;
    virtual void handle_button(u32 button, bool pressed) = 0;
};

} // namespace acos::input
