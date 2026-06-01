#include "linux_syscalls.h"
#include <kernel/vfs/vfs.h>
namespace acos::compat::linux {
u64 linux_syscall_dispatch(u64 num, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5) {
    (void)a4; (void)a5;
    return 0;
}
}
