#pragma once
#include <acos/types.h>

namespace acos::compat::linux {

enum class LinuxSyscallNum : u64 {
    READ            = 0,
    WRITE           = 1,
    OPEN            = 2,
    CLOSE           = 3,
    STAT            = 4,
    FSTAT           = 5,
    LSEEK           = 8,
    MMAP            = 9,
    MPROTECT        = 10,
    MUNMAP          = 11,
    RT_SIGACTION    = 13,
    RT_SIGPROCMASK  = 14,
    IOCTL           = 16,
    SELECT          = 23,
    NANOSLEEP       = 35,
    GETPID          = 39,
    SOCKET          = 41,
    CONNECT         = 42,
    ACCEPT          = 43,
    SENDTO          = 44,
    RECVFROM        = 45,
    BIND            = 49,
    LISTEN          = 50,
    CLONE           = 56,
    FORK            = 57,
    EXECVE          = 59,
    EXIT            = 60,
    WAIT4           = 61,
    KILL            = 62,
    FCNTL           = 72,
    GETCWD          = 79,
    MKDIR           = 83,
    RMDIR           = 84,
    GETTIMEOFDAY    = 96,
    POLL            = 7,
    ARCH_PRCTL      = 158,
    CLOCK_GETTIME   = 228,
    EXIT_GROUP      = 231,
    EPOLL_CREATE    = 213
};

u64 linux_syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5);

} // namespace acos::compat::linux
