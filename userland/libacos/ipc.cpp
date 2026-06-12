#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/ipc.h>
#include <acos/syscall.h>

namespace acos::ipc {

Channel::Channel() {
    m_handle = acos::syscall(103); // SyscallNum::ChannelCreate
}

bool Channel::send(const Message& msg) {
    return acos::syscall(100, m_handle, (u64)&msg) == 0;
}

bool Channel::receive(Message& msg, bool block [[maybe_unused]]) {
    // block is ignored for now or handled by kernel
    return acos::syscall(101, m_handle, (u64)&msg) == 0;
}

u64 channel_create() {
    return acos::syscall(103); // SyscallNum::ChannelCreate
}

bool channel_send(u64 handle, const void* data, usize size) {
    Message msg = {0, 0, 0, 0, size, const_cast<void*>(data), 0};
    return acos::syscall(100, handle, (u64)&msg) == 0;
}

bool channel_receive(u64 handle, void* data, usize size) {
    Message msg = {0, 0, 0, 0, size, data, 0};
    return acos::syscall(101, handle, (u64)&msg) == 0;
}

} // namespace acos::ipc

namespace acos::services {

bool register_service(const char* name, u64 channel_handle) {
    return acos::syscall(501, (u64)name, channel_handle) == 0;
}

u64 locate_service(const char* name) {
    return acos::syscall(500, (u64)name);
}

} // namespace acos::services
