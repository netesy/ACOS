#pragma once
#include <kernel/net/socket.h>
#include <kernel/ipc/channel.h>

namespace acos::net {

enum class TCPState {
    Closed,
    Listen,
    SynSent,
    SynReceived,
    Established,
    FinWait1,
    FinWait2,
    CloseWait,
    Closing,
    LastAck,
    TimeWait
};

class TCPSocket : public Socket {
public:
    TCPSocket();
    ~TCPSocket() override = default;

    i32 bind(u32 ip, u16 port) override;
    i32 listen(int backlog) override;
    i32 accept() override;
    i32 connect(u32 ip, u16 port) override;
    i32 send(const void* buffer, usize size) override;
    i32 recv(void* buffer, usize size) override;
    void close() override;

    void handle_packet(const void* data, usize size);

private:
    u32 m_local_ip, m_remote_ip;
    u16 m_local_port, m_remote_port;
    TCPState m_state;
    u32 m_seq_num, m_ack_num;

    acos::ipc::Channel m_rx_buffer;
};

} // namespace acos::net
