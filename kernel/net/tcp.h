#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

struct TCPHeader {
    u16 src_port;
    u16 dest_port;
    u32 seq_num;
    u32 ack_num;
    u16 flags;
    u16 window;
    u16 checksum;
    u16 urgent_ptr;
} __attribute__((packed));

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

struct TCPConnection {
    TCPState state;
    u32 local_ip;
    u16 local_port;
    u32 remote_ip;
    u16 remote_port;
    u32 snd_una;
    u32 snd_nxt;
    u32 rcv_nxt;
    u16 snd_wnd;
    u16 rcv_wnd;
    u32 cwnd;        // Congestion Window
    u32 ssthresh;    // Slow Start Threshold
    u32 dup_acks;    // Duplicate ACK counter
    u32 srtt;        // Smoothed Round Trip Time
    u32 rto;         // Retransmission Timeout
    bool active;
};

class TCP {
public:
    static void handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size);
    static TCPConnection* find_connection(u32 local_ip, u16 local_port, u32 remote_ip, u16 remote_port);
    static TCPConnection* create_connection(u32 local_ip, u16 local_port, u32 remote_ip, u16 remote_port);
};

} // namespace acos::net
