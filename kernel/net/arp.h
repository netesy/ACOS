#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

struct ARPHeader {
    u16 hw_type;
    u16 proto_type;
    u8 hw_addr_len;
    u8 proto_addr_len;
    u16 opcode;
    MACAddress src_mac;
    u32 src_ip;
    MACAddress dest_mac;
    u32 dest_ip;
} __attribute__((packed));

class ARP {
public:
    static void handle_packet(NetDevice* dev, const void* data, usize size);
    static void resolve(NetDevice* dev, u32 ip);
};

} // namespace acos::net
