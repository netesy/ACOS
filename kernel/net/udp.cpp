#include <kernel/net/udp.h>

namespace acos::net {

void UDP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    (void)dev; (void)src_ip; (void)data; (void)size;
}

bool UDP::send_packet(NetDevice* dev, u32 dest_ip, u16 src_port, u16 dest_port, const void* data, usize size) {
    (void)dev; (void)dest_ip; (void)src_port; (void)dest_port; (void)data; (void)size;
    return true;
}

} // namespace acos::net
