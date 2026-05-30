#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

struct EthernetHeader {
    MACAddress dest;
    MACAddress src;
    u16 type;
} __attribute__((packed));

class Ethernet {
public:
    static void handle_packet(NetDevice* dev, const void* data, usize size);
    static bool send_packet(NetDevice* dev, const MACAddress& dest, u16 type, const void* data, usize size);
};

} // namespace acos::net
