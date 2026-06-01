#include <kernel/net/tcp.h>

namespace acos::net {

void TCP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    if (!dev || !data || size < 20) return;
    
    const u8* packet = (const u8*)data;
    u16 src_port = (packet[0] << 8) | packet[1];
    u16 dst_port = (packet[2] << 8) | packet[3];
    u32 seq_num = ((u32)packet[4] << 24) | ((u32)packet[5] << 16) | ((u32)packet[6] << 8) | packet[7];
    u32 ack_num = ((u32)packet[8] << 24) | ((u32)packet[9] << 16) | ((u32)packet[10] << 8) | packet[11];
    u8 flags = packet[13];
    u16 window = (packet[14] << 8) | packet[15];
    
    // Parse flags
    bool syn = (flags & 0x02) != 0;
    bool ack = (flags & 0x10) != 0;
    bool fin = (flags & 0x01) != 0;
    bool rst = (flags & 0x04) != 0;
    
    // Payload starts after TCP header (minimum 20 bytes)
    u8 header_len = ((packet[12] >> 4) & 0x0F) * 4;
    if (header_len < 20 || header_len > size) return;
    
    const void* payload = (const u8*)data + header_len;
    usize payload_size = size - header_len;
    
    // Connection state machine
    if (syn && !ack) {
        // SYN received - send SYN-ACK
    } else if (syn && ack) {
        // SYN-ACK received - connection established
    } else if (ack && !fin) {
        // Data ACK - enqueue payload
    } else if (fin) {
        // FIN received - close connection
    }
    
    (void)src_ip;
    (void)src_port;
    (void)dst_port;
    (void)seq_num;
    (void)ack_num;
    (void)window;
    (void)rst;
    (void)payload;
    (void)payload_size;
}

} // namespace acos::net
