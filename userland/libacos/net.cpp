#include <acos/net.h>
#include <acos/syscall.h>

namespace acos::net {

Socket::Socket() {
    m_handle = syscall(sys::SyscallNum::SocketCreate);
}

i32 Socket::set_option(u32 level, u32 option, const void* val, usize len) {
    return (i32)syscall(sys::SyscallNum::SocketSetOpt, m_handle, level, option, reinterpret_cast<u64>(val), len);
}

i32 Socket::set_window_scale(u8 scale_shift) {
    u32 shift_val = scale_shift;
    return set_option(1, 10 /* TCP_WINDOW_SCALE */, &shift_val, sizeof(shift_val));
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

TCPSocket::TCPSocket() : Socket(), m_state(TCPState::Closed), m_options{1460, 7, true}, m_cwnd(1460) {}

i32 TCPSocket::connect_with_options(const char* ip, u16 port, const TCPOptions& opts) {
    m_options = opts;
    m_state = TCPState::SynSent;

    set_window_scale(opts.window_scale);
    i32 res = connect(ip, port);
    if (res == 0) {
        m_state = TCPState::Established;
        m_cwnd = opts.mss * 2; // Initial congestion window (Slow Start)
    } else {
        m_state = TCPState::Closed;
    }
    return res;
}

UDPSocket::UDPSocket() : Socket() {}

} // namespace acos::net
