#include <kernel/net/udp.h>

namespace acos::net {

void UDP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    if (!dev || !data || size < 8) return;
    
    const u8* packet = (const u8*)data;
    u16 src_port = (packet[0] << 8) | packet[1];
    u16 dst_port = (packet[2] << 8) | packet[3];
    u16 length = (packet[4] << 8) | packet[5];
    u16 checksum = (packet[6] << 8) | packet[7];
    
    if (length < 8 || length > size) return;
    
    // Validate checksum if non-zero
    if (checksum != 0) {
        u32 sum = 0;
        const u16* ptr = (const u16*)packet;
        for (usize i = 0; i < length / 2; i++) {
            sum += ptr[i];
        }
        if (length & 1) sum += packet[length - 1];
        
        while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
        if ((u16)~sum != checksum) return;
    }
    
    // Payload starts at offset 8
    const void* payload = (const u8*)data + 8;
    usize payload_size = length - 8;
    
    // Dispatch to socket layer (would be implemented in socket manager)
    (void)src_ip;
    (void)src_port;
    (void)dst_port;
    (void)payload;
    (void)payload_size;
}

bool UDP::send_packet(NetDevice* dev, u32 dest_ip, u16 src_port, u16 dest_port, const void* data, usize size) {
    if (!dev || !data || size > 65527) return false;
    
    u8 packet[65535];
    packet[0] = (src_port >> 8) & 0xFF;
    packet[1] = src_port & 0xFF;
    packet[2] = (dest_port >> 8) & 0xFF;
    packet[3] = dest_port & 0xFF;
    
    u16 length = size + 8;
    packet[4] = (length >> 8) & 0xFF;
    packet[5] = length & 0xFF;
    packet[6] = 0;
    packet[7] = 0;
    
    acos::runtime::memcpy(packet + 8, data, size);
    
    // Calculate checksum
    u32 sum = 0;
    u16* ptr = (u16*)packet;
    for (usize i = 0; i < length / 2; i++) {
        sum += ptr[i];
    }
    if (length & 1) sum += packet[length - 1];
    
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    u16 checksum = ~sum;
    if (checksum == 0) checksum = 0xFFFF;
    
    packet[6] = (checksum >> 8) & 0xFF;
    packet[7] = checksum & 0xFF;
    
    // Pass to IPv4 layer
    return true;
}

} // namespace acos::net
