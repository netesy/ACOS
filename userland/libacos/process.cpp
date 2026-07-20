#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>

namespace acos::process {

Thread::Thread(void (*entry)(void*), void* arg) {
    m_handle = create_thread(entry, arg);
}

void Thread::start() {
    start_thread(m_handle);
}

void Thread::join() {
    syscall(sys::SyscallNum::ThreadJoin, m_handle, 0, 0, 0, 0);
}

void Thread::terminate() {
    syscall(sys::SyscallNum::ThreadTerminate, m_handle, 0, 0, 0, 0);
}

Process::Process(const char* path) {
    m_handle = syscall(sys::SyscallNum::ProcessCreate, reinterpret_cast<u64>(path), 0, 0, 0, 0);
}

void Process::start() {
    syscall(sys::SyscallNum::ProcessStart, m_handle, 0, 0, 0, 0);
}

void Process::terminate() {
    syscall(sys::SyscallNum::ProcessTerminate, m_handle, 0, 0, 0, 0);
}

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

void sleep(u64 ms) {
    syscall(sys::SyscallNum::ThreadSleep, ms, 0, 0, 0, 0);
}

void yield() {
    syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0);
}

int args_count() {
    return 1;
}

const char* get_arg(int index) {
    if (index == 0) return "asade_app";
    return nullptr;
}

} // namespace acos::process
