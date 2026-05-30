#include <kernel/syscall/syscall.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::syscall {

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
    (void)arg1; (void)arg2; (void)arg3; (void)arg4; (void)arg5;

    switch (static_cast<SyscallNum>(num)) {
        case SyscallNum::GetPid:
            // return scheduler::current_process()->id;
            return 123;
        case SyscallNum::Yield:
            scheduler::schedule();
            return 0;
        default:
            return static_cast<u64>(-1);
    }
}

} // namespace acos::syscall
