#pragma once
#include <acos/types.h>
#include <kernel/net/net_device.h>

namespace acos::net {

class NetworkManager {
public:
    static void register_device(NetDevice* dev);
    static NetDevice* get_device(u32 index);
    static void init();
    static void handle_packet(NetDevice* dev, const void* data, usize size);

private:
    static NetDevice* g_devices[8];
    static u32 g_device_count;
};

} // namespace acos::net
