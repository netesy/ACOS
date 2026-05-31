#pragma once
#include <acos/types.h>

namespace acos::syscall {

enum class SyscallNum : u64 {
    // Process/Thread (0-99)
    Exit = 1,
    Yield = 2,
    GetPid = 3,
    ThreadCreate = 4,
    ThreadSleep = 5,

    // IPC (100-199)
    ChannelSend = 100,
    ChannelReceive = 101,
    ChannelCall = 102,
    NotificationSignal = 110,
    NotificationWait = 111,

    // Memory (200-299)
    MemoryMap = 200,
    MemoryUnmap = 201,
    MemoryProtect = 202,

    // VFS/Storage (300-399)
    FileOpen = 300,
    FileClose = 301,
    FileRead = 302,
    FileWrite = 303,
    FileSeek = 304,

    // Network (400-499)
    SocketCreate = 400,
    SocketBind = 401,
    SocketConnect = 402,
    SocketSend = 403,
    SocketReceive = 404
};

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5);

} // namespace acos::syscall
