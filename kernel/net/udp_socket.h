#pragma once
#include <kernel/net/socket.h>
#include <kernel/ipc/channel.h>

namespace acos::net {

class UDPSocket : public Socket {
public:
    UDPSocket();
    ~UDPSocket() override = default;

    i32 bind(u32 ip, u16 port) override;
    i32 listen(int backlog) override { (void)backlog; return -1; }
    i32 accept() override { return -1; }
    i32 connect(u32 ip, u16 port) override;
    i32 send(const void* buffer, usize size) override;
    i32 recv(void* buffer, usize size) override;
    void close() override;

    void handle_incoming(u32 src_ip, u16 src_port, const void* data, usize size);

private:
    u32 m_local_ip;
    u16 m_local_port;
    u32 m_remote_ip;
    u16 m_remote_port;
    bool m_connected;

    acos::ipc::Channel m_rx_buffer;
};

} // namespace acos::net
