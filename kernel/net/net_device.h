#pragma once
#include <acos/types.h>

namespace acos::net {

struct MACAddress {
    u8 octets[6];
};

class NetDevice {
public:
    virtual ~NetDevice() = default;
    virtual bool send_packet(const void* data, usize size) = 0;
    virtual usize receive_packet(void* buffer, usize max_size) = 0;

    virtual MACAddress mac() const = 0;
    virtual u32 mtu() const = 0;
};

class NetworkManager {
public:
    static void register_device(NetDevice* dev);
    static NetDevice* get_device(u32 index);
private:
    static NetDevice* g_devices[8];
    static u32 g_device_count;
};

} // namespace acos::net
