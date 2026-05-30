#include <kernel/net/udp_socket.h>
#include <kernel/net/udp.h>

namespace acos::net {

UDPSocket::UDPSocket() : m_local_ip(0), m_local_port(0), m_remote_ip(0), m_remote_port(0), m_connected(false) {}

i32 UDPSocket::bind(u32 ip, u16 port) {
    m_local_ip = ip;
    m_local_port = port;
    return 0;
}

i32 UDPSocket::connect(u32 ip, u16 port) {
    m_remote_ip = ip;
    m_remote_port = port;
    m_connected = true;
    return 0;
}

i32 UDPSocket::send(const void* buffer, usize size) {
    if (!m_connected) return -1;
    if (UDP::send_packet(nullptr, m_remote_ip, m_local_port, m_remote_port, buffer, size)) {
        return static_cast<i32>(size);
    }
    return -1;
}

i32 UDPSocket::recv(void* buffer, usize size) {
    acos::ipc::Message msg;
    if (m_rx_buffer.receive(msg, true)) {
        usize copy_size = (msg.size < size) ? msg.size : size;
        // In a real implementation, payload would be copied from kernel buffer
        (void)buffer; (void)copy_size;
        return static_cast<i32>(copy_size);
    }
    return -1;
}

void UDPSocket::close() {
    m_connected = false;
}

void UDPSocket::handle_incoming(u32 src_ip, u16 src_port, const void* data, usize size) {
    (void)src_ip; (void)src_port; (void)data; (void)size;
    // Push into m_rx_buffer
}

} // namespace acos::net
