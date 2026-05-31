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

class TCP {
public:
    static void handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size);
};

} // namespace acos::net
