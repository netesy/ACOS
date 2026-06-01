#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
enum class LinuxSyscallNum : u64 { READ = 0, WRITE = 1, OPEN = 2, CLOSE = 3, GETPID = 39, EXIT = 60 };
u64 linux_syscall_dispatch(u64 num, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5);
}
