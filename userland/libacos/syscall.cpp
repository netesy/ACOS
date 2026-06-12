#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>

namespace acos {

u64 syscall(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
    u64 ret;
    register u64 r10 asm("r10") = arg3;
    register u64 r8  asm("r8")  = arg4;
    register u64 r9  asm("r9")  = arg5;
    
    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(num), "D"(arg1), "S"(arg2), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );
    return ret;
}

} // namespace acos
