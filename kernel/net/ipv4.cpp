#include <kernel/net/ipv4.h>

namespace acos::net {

void IPv4::handle_packet(NetDevice* dev, const void* data, usize size) {
    if (!dev || !data || size < 20) return;
    
    const u8* packet = (const u8*)data;
    u8 version_ihl = packet[0];
    u8 version = (version_ihl >> 4) & 0x0F;
    u8 ihl = (version_ihl & 0x0F) * 4;
    
    if (version != 4 || ihl < 20 || ihl > size) return;
    
    u16 total_length = (packet[2] << 8) | packet[3];
    if (total_length > size) return;
    
    u16 checksum = (packet[10] << 8) | packet[11];
    u8 protocol = packet[9];
    u32 src_ip = ((u32)packet[12] << 24) | ((u32)packet[13] << 16) | ((u32)packet[14] << 8) | packet[15];
    u32 dst_ip = ((u32)packet[16] << 24) | ((u32)packet[17] << 16) | ((u32)packet[18] << 8) | packet[19];
    
    // Verify checksum
    u32 sum = 0;
    u16* ptr = (u16*)packet;
    for (int i = 0; i < ihl / 2; i++) {
        if (i != 5) sum += ptr[i];
    }
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    if ((u16)~sum != checksum) return;
    
    // Dispatch to protocol handler
    const void* payload = (const u8*)data + ihl;
    usize payload_size = total_length - ihl;
    
    if (protocol == 17) {
        // UDP
        UDP::handle_packet(dev, src_ip, payload, payload_size);
    } else if (protocol == 6) {
        // TCP
        TCP::handle_packet(dev, src_ip, payload, payload_size);
    } else if (protocol == 1) {
        // ICMP
    }
    
    (void)dst_ip;
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
