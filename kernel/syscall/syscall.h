#pragma once
#include <acos/types.h>

namespace acos::syscall {

enum class SyscallNum : u64 {
    GetPid = 1,
    Yield = 2,
    SendMessage = 3,
    ReceiveMessage = 4
};

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5);

} // namespace acos::syscall
