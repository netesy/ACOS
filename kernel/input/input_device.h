#pragma once
#include <acos/types.h>
#include <acos/abi/input.h>

namespace acos::input {

using InputType = abi::InputType;
using InputEvent = abi::InputEvent;

class InputDevice {
public:
    virtual ~InputDevice() = default;
    virtual bool initialize() = 0;
    virtual InputType type() const = 0;
    virtual const char* name() const = 0;
};

} // namespace acos::input
