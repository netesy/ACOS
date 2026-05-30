#include <kernel/net/tcp_socket.h>

namespace acos::net {

TCPSocket::TCPSocket() : m_state(TCPState::Closed), m_seq_num(0), m_ack_num(0) {}

i32 TCPSocket::bind(u32 ip, u16 port) {
    m_local_ip = ip;
    m_local_port = port;
    return 0;
}

i32 TCPSocket::listen(int backlog) {
    (void)backlog;
    m_state = TCPState::Listen;
    return 0;
}

i32 TCPSocket::accept() {
    // Block until connection established
    return 0;
}

i32 TCPSocket::connect(u32 ip, u16 port) {
    m_remote_ip = ip;
    m_remote_port = port;
    m_state = TCPState::SynSent;
    // Send SYN packet
    return 0;
}

i32 TCPSocket::send(const void* buffer, usize size) {
    (void)buffer; (void)size;
    return 0;
}

i32 TCPSocket::recv(void* buffer, usize size) {
    (void)buffer; (void)size;
    return 0;
}

void TCPSocket::close() {
    m_state = TCPState::Closed;
}

void TCPSocket::handle_packet(const void* data, usize size) {
    (void)data; (void)size;
    // TCP State machine logic: transition between SYN, ESTABLISHED, FIN, etc.
}

} // namespace acos::net
