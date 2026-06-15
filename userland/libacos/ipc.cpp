#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/ipc.h>
#include <acos/syscall.h>

namespace acos::ipc {

Channel::Channel() {
    m_handle = syscall(sys::SyscallNum::ChannelCreate);
}

bool Channel::send(const Message& msg) {
    return syscall(sys::SyscallNum::ChannelSend, m_handle, (u64)&msg) == 0;
}

bool Channel::receive(Message& msg, bool block [[maybe_unused]]) {
    // block is ignored for now or handled by kernel
    return syscall(sys::SyscallNum::ChannelReceive, m_handle, (u64)&msg) == 0;
}

u64 channel_create() {
    return syscall(sys::SyscallNum::ChannelCreate);
}

bool channel_send(u64 handle, const void* data, usize size) {
    Message msg = {0, 0, 0, 0, size, const_cast<void*>(data), 0};
    return syscall(sys::SyscallNum::ChannelSend, handle, (u64)&msg) == 0;
}

bool channel_receive(u64 handle, void* data, usize size) {
    Message msg = {0, 0, 0, 0, size, data, 0};
    return syscall(sys::SyscallNum::ChannelReceive, handle, (u64)&msg) == 0;
}

} // namespace acos::ipc

namespace acos::services {

bool register_service(const char* name, u64 channel_handle) {
    return syscall(sys::SyscallNum::ResourceRegister, (u64)name, channel_handle) == 0;
}

u64 locate_service(const char* name) {
    return syscall(sys::SyscallNum::ResourceLocate, (u64)name);
}

} // namespace acos::services
