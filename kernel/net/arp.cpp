#include <kernel/net/arp.h>

namespace acos::net {

void ARP::handle_packet(NetDevice* dev, const void* data, usize size) {
    (void)dev; (void)data; (void)size;
}

void ARP::resolve(NetDevice* dev, u32 ip) {
    (void)dev; (void)ip;
}

} // namespace acos::net
