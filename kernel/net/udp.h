#pragma once
#include <acos/types.h>
#include <kernel/net/ipv4.h>

namespace acos::net {

struct UDPHeader {
    u16 src_port;
    u16 dest_port;
    u16 length;
    u16 checksum;
} __attribute__((packed));

class UDP {
public:
    static void handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size);
    static bool send_packet(NetDevice* dev, u32 dest_ip, u16 src_port, u16 dest_port, const void* data, usize size);
};

} // namespace acos::net
