#include "linux_syscalls.h"
#include <kernel/scheduler/scheduler.h>
#include <kernel/vfs/vfs.h>

namespace acos::compat::linux {

u64 linux_syscall_dispatch(u64 num, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5) {
    (void)a4;
    (void)a5;

    switch (static_cast<LinuxSyscallNum>(num)) {
        case LinuxSyscallNum::READ:
            return static_cast<u64>(vfs::VFS::read(a1, reinterpret_cast<void*>(a2), a3));
        case LinuxSyscallNum::WRITE:
            return static_cast<u64>(vfs::VFS::write(a1, reinterpret_cast<const void*>(a2), a3));
        case LinuxSyscallNum::OPEN:
            return static_cast<u64>(vfs::VFS::open(reinterpret_cast<const char*>(a1), a2));
        case LinuxSyscallNum::CLOSE:
            return static_cast<u64>(vfs::VFS::close(a1));
        case LinuxSyscallNum::GETPID: {
            scheduler::Thread* thread = scheduler::current_thread();
            return (thread && thread->parent) ? thread->parent->id : 0;
        }
        case LinuxSyscallNum::EXIT: {
            scheduler::Thread* thread = scheduler::current_thread();
            if (thread) {
                thread->return_value = reinterpret_cast<void*>(a1);
                thread->state = scheduler::ThreadState::Terminated;
                scheduler::schedule();
            }
            return 0;
        }
    }

    return static_cast<u64>(-1);
}

} // namespace acos::compat::linux
