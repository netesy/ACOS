#pragma once
#include <acos/types.h>
#include <acos/abi/input.h>

namespace acos::input {

using InputType = abi::InputType;
using InputEvent = abi::InputEvent;
using VirtualKey = abi::VirtualKey;

// Userspace APIs
u64 create_queue();
bool pop_event(u64 queue_handle, InputEvent& event, bool block);
u64 open_device(InputType type);
void set_focused_process(u64 pid);

} // namespace acos::input
