#pragma once
#include <acos/types.h>
#include <acos/syscall_nums.h>

namespace acos {

u64 syscall(u64 num, u64 arg1 = 0, u64 arg2 = 0, u64 arg3 = 0, u64 arg4 = 0, u64 arg5 = 0);

inline u64 syscall(sys::SyscallNum num, u64 arg1 = 0, u64 arg2 = 0, u64 arg3 = 0, u64 arg4 = 0, u64 arg5 = 0) {
    return syscall(static_cast<u64>(num), arg1, arg2, arg3, arg4, arg5);
}

} // namespace acos
