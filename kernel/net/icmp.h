#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

struct ICMPHeader {
    u8 type;
    u8 code;
    u16 checksum;
    u16 id;
    u16 sequence;
} __attribute__((packed));

class ICMP {
public:
    static void handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size);
};

} // namespace acos::net
