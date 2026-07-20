#include <acos/net.h>
#include <acos/syscall.h>

namespace acos::net {

Socket::Socket() {
    m_handle = syscall(sys::SyscallNum::SocketCreate);
}

Socket::~Socket() {
    close();
}

i32 Socket::bind(const char* ip, u16 port) {
    return (i32)syscall(sys::SyscallNum::SocketBind, m_handle, reinterpret_cast<u64>(ip), port, 0, 0);
}

i32 Socket::connect(const char* ip, u16 port) {
    return (i32)syscall(sys::SyscallNum::SocketConnect, m_handle, reinterpret_cast<u64>(ip), port, 0, 0);
}

i32 Socket::send(const void* buf, usize size) {
    return (i32)syscall(sys::SyscallNum::SocketSend, m_handle, reinterpret_cast<u64>(buf), size, 0, 0);
}

i32 Socket::receive(void* buf, usize size) {
    return (i32)syscall(sys::SyscallNum::SocketReceive, m_handle, reinterpret_cast<u64>(buf), size, 0, 0);
}

i32 Socket::close() {
    if (m_handle != 0 && m_handle != static_cast<u64>(-1)) {
        i32 res = (i32)syscall(sys::SyscallNum::ResourceClose, m_handle, 0, 0, 0, 0);
        m_handle = 0;
        return res;
    }
    return 0;
}

TCPSocket::TCPSocket() : Socket() {}

UDPSocket::UDPSocket() : Socket() {}

} // namespace acos::net
