#include <kernel/net/net_device.h>

namespace acos::net {

NetDevice* NetworkManager::g_devices[8];
u32 NetworkManager::g_device_count = 0;

void NetworkManager::register_device(NetDevice* dev) {
    if (g_device_count < 8) {
        g_devices[g_device_count++] = dev;
    }
}

NetDevice* NetworkManager::get_device(u32 index) {
    if (index < g_device_count) return g_devices[index];
    return nullptr;
}

} // namespace acos::net
