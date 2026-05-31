#include <kernel/syscall/syscall.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/ipc/channel.h>
#include <kernel/ipc/notification.h>
#include <kernel/vfs/file.h>
#include <kernel/vfs/vfs.h>

namespace acos::syscall {

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
    auto* current_thr = scheduler::current_thread();
    if (!current_thr && num != static_cast<u64>(SyscallNum::Yield)) {
        return static_cast<u64>(-1);
    }

    auto* current = current_thr ? current_thr->parent : nullptr;

    switch (static_cast<SyscallNum>(num)) {
        case SyscallNum::Exit:
            if (current_thr) {
                current_thr->state = scheduler::ThreadState::Terminated;
                scheduler::schedule();
            }
            return 0;

        case SyscallNum::Yield:
            scheduler::schedule();
            return 0;

        case SyscallNum::GetPid:
            return current ? current->id : 0;

        // IPC: Channel Operations
        case SyscallNum::ChannelSend: {
            u64 handle = arg1;
            const void* data = reinterpret_cast<const void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            auto* chan = current->get_channel(handle);
            if (!chan) return static_cast<u64>(-2);
            return static_cast<u64>(chan->send(data, size));
        }

        case SyscallNum::ChannelReceive: {
            u64 handle = arg1;
            void* buffer = reinterpret_cast<void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            auto* chan = current->get_channel(handle);
            if (!chan) return static_cast<u64>(-2);
            return static_cast<u64>(chan->receive(buffer, size));
        }

        // IPC: Notification Operations
        case SyscallNum::NotificationSignal: {
            u64 handle = arg1;
            if (!current) return static_cast<u64>(-1);
            auto* note = current->get_notification(handle);
            if (!note) return static_cast<u64>(-2);
            note->signal();
            return 0;
        }

        case SyscallNum::NotificationWait: {
            u64 handle = arg1;
            if (!current) return static_cast<u64>(-1);
            auto* note = current->get_notification(handle);
            if (!note) return static_cast<u64>(-2);
            note->wait();
            return 0;
        }

        // VFS Operations
        case SyscallNum::FileOpen: {
            const char* path = reinterpret_cast<const char*>(arg1);
            u64 flags = arg2;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::open(path, flags));
        }

        case SyscallNum::FileClose: {
            u64 fd = arg1;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::close(fd));
        }

        case SyscallNum::FileRead: {
            u64 fd = arg1;
            void* buffer = reinterpret_cast<void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::read(fd, buffer, size));
        }

        case SyscallNum::FileWrite: {
            u64 fd = arg1;
            const void* data = reinterpret_cast<const void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::write(fd, data, size));
        }

        default:
            return static_cast<u64>(-1);
    }
}

} // namespace acos::syscall
