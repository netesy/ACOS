#include <kernel/net/ipv4.h>

namespace acos::net {

void IPv4::handle_packet(NetDevice* dev, const void* data, usize size) {
    (void)dev; (void)data; (void)size;
}

u16 IPv4::calculate_checksum(const void* data, usize size) {
    const u16* ptr = reinterpret_cast<const u16*>(data);
    u32 sum = 0;
    while (size > 1) {
        sum += *ptr++;
        size -= 2;
    }
    if (size == 1) sum += *reinterpret_cast<const u8*>(ptr);
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return ~static_cast<u16>(sum);
}

} // namespace acos::net
