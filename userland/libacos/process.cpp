#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::process {

u64 get_pid() {
    return acos::syscall(3); // SyscallNum::GetPid
}

void exit(int status) {
    acos::syscall(1, status); // SyscallNum::Exit
}

void log(const char* msg) {
    acos::syscall(303, 1, (u64)msg, strlen(msg)); // SyscallNum::FileWrite to stdout(1)
}

void log(const char* msg, unsigned int len) {
    acos::syscall(303, 1, (u64)msg, len);
}

} // namespace acos::process
