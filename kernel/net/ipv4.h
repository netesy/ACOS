#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

struct IPv4Header {
    u8 version_ihl;
    u8 tos;
    u16 length;
    u16 id;
    u16 flags_fragment;
    u8 ttl;
    u8 protocol;
    u16 checksum;
    u32 src_ip;
    u32 dest_ip;
} __attribute__((packed));

class IPv4 {
public:
    static void handle_packet(NetDevice* dev, const void* data, usize size);
    static u16 calculate_checksum(const void* data, usize size);
};

} // namespace acos::net
