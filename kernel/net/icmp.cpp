#include <kernel/net/icmp.h>

namespace acos::net {

void ICMP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    (void)dev; (void)src_ip; (void)data; (void)size;
}

} // namespace acos::net
