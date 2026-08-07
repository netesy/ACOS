#pragma once
#include <acos/types.h>

namespace acos::sys {

enum class SyscallNum : u64 {
    // Process/Thread (0-99)
    Exit = 1,
    Yield = 2,
    GetPid = 3,
    ProcessCreate = 4,
    ProcessStart = 5,
    ProcessTerminate = 6,
    Fork = 7,
    WaitPid = 8,
    ThreadCreate = 10,
    ThreadSleep = 11,
    ThreadJoin = 12,
    ThreadTerminate = 13,

    ResourceClose = 20,
    ResourceQuery = 21,
    ResourceDuplicate = 22,
    ResourceTransfer = 23,
    ResourceRevoke = 24,

    // IPC (100-199)
    ChannelSend = 100,
    ChannelReceive = 101,
    ChannelCall = 102,
    ChannelCreate = 103,
    NotificationCreate = 109,
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
    FileReadDir = 305,
    FileMkdir = 306,
    FileUnlink = 307,
    FileRmdir = 308,
    PipeCreate = 310,
    FileDup = 311,

    // Network (400-499)
    SocketCreate = 400,
    SocketBind = 401,
    SocketConnect = 402,
    SocketSend = 403,
    SocketReceive = 404,

    // Graphics (600-699)
    GraphicsSurfaceCreate = 600,
    GraphicsWindowCreate = 601,
    GraphicsPresent = 602,
    GraphicsGetFramebuffer = 603,
    GraphicsDisplayCreate = 604,
    GraphicsBufferCreate = 605,
    GraphicsResourceDestroy = 606,
    GraphicsResourceResize = 607,
    GraphicsContextCreate = 610,
    GraphicsPutPixel = 611,
    GraphicsDrawLine = 612,
    GraphicsDrawRect = 613,
    GraphicsFillRect = 614,
    GraphicsDrawCircle = 615,
    GraphicsFillCircle = 616,
    GraphicsBlit = 617,
    GraphicsClear = 618,
    GraphicsCopyRect = 619,

    // Input Subsystem (710-719)
    InputQueueCreate = 710,
    InputQueuePop = 711,
    InputDeviceOpen = 712,

    // Service Discovery (500-599)
    ResourceLocate = 500,
    ResourceRegister = 501
};

struct ResourceInfo {
    u64 type;
    u64 id;
    u64 rights;
    u64 owner;
    u64 state;
};

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5);

} // namespace acos::sys
