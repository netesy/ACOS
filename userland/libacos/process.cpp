#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::process {

u64 get_pid() {
    return syscall(sys::SyscallNum::GetPid);
}

void exit(int status) {
    syscall(sys::SyscallNum::Exit, status);
}

void log(const char* msg) {
    syscall(sys::SyscallNum::FileWrite, 1, (u64)msg, strlen(msg));
}

void log(const char* msg, unsigned int len) {
    syscall(sys::SyscallNum::FileWrite, 1, (u64)msg, len);
}

} // namespace acos::process
