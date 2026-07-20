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

u64 create_thread(void (*entry)(void*), void* arg) {
    return syscall(sys::SyscallNum::ThreadCreate, 0, reinterpret_cast<u64>(entry), reinterpret_cast<u64>(arg), 0, 0);
}

void start_thread(u64 thread_handle) {
    syscall(sys::SyscallNum::ProcessStart, thread_handle, 0, 0, 0, 0);
}

} // namespace acos::process
