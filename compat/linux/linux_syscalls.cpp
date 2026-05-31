#include "linux_syscalls.h"
#include <kernel/syscall/syscall.h>
#include <kernel/vfs/vfs.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/net/socket.h>
#include "linux_errno.h"

namespace acos::compat::linux {

u64 linux_syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
    (void)arg4; (void)arg5;

    switch (static_cast<LinuxSyscallNum>(num)) {
        case LinuxSyscallNum::READ:
            return static_cast<u64>(acos::vfs::VFS::read(arg1, reinterpret_cast<void*>(arg2), arg3));

        case LinuxSyscallNum::WRITE:
            return static_cast<u64>(acos::vfs::VFS::write(arg1, reinterpret_cast<const void*>(arg2), arg3));

        case LinuxSyscallNum::OPEN:
            return acos::vfs::VFS::open(reinterpret_cast<const char*>(arg1), arg2);

        case LinuxSyscallNum::CLOSE:
            return acos::vfs::VFS::close(arg1);

        case LinuxSyscallNum::LSEEK:
            // Mapped to ACOS VFS seek logic
            return 0;

        case LinuxSyscallNum::GETPID: {
            auto* thr = acos::scheduler::current_thread();
            return thr ? thr->parent->id : 0;
        }

        case LinuxSyscallNum::EXIT:
        case LinuxSyscallNum::EXIT_GROUP: {
            auto* thr = acos::scheduler::current_thread();
            if (thr) {
                thr->state = acos::scheduler::ThreadState::Terminated;
                acos::scheduler::schedule();
            }
            return 0;
        }

        case LinuxSyscallNum::SOCKET:
            // return acos::net::Socket::create(arg1, arg2, arg3);
            return 0;

        case LinuxSyscallNum::BIND:
            // return acos::net::Socket::bind(arg1, (sockaddr*)arg2, arg3);
            return 0;

        default:
            return static_cast<u64>(-38); // Linux ENOSYS
    }
}

} // namespace acos::compat::linux
