#include <acos/input.h>
#include <acos/syscall.h>
#include <acos/syscall_nums.h>

namespace acos::input {

u64 create_queue() {
    return syscall(sys::SyscallNum::InputQueueCreate, 0, 0, 0, 0, 0);
}

bool pop_event(u64 queue_handle, InputEvent& event, bool block) {
    u64 res = syscall(sys::SyscallNum::InputQueuePop, queue_handle, reinterpret_cast<u64>(&event), block ? 1 : 0, 0, 0);
    return res == 1;
}

u64 open_device(InputType type) {
    return syscall(sys::SyscallNum::InputDeviceOpen, static_cast<u64>(type), 0, 0, 0, 0);
}

void set_focused_process(u64 pid) {
    syscall(sys::SyscallNum::InputFocusSet, pid, 0, 0, 0, 0);
}

} // namespace acos::input
