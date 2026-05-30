#include <kernel/net/udp.h>
#include <kernel/net/udp_socket.h>
#include <kernel/hal/spinlock.h>

namespace acos::net {

static UDPSocket* g_udp_sockets[128];
static usize g_udp_socket_count = 0;
static hal::SpinLock g_udp_lock;

void UDP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    if (size < sizeof(UDPHeader)) return;
    const UDPHeader* header = reinterpret_cast<const UDPHeader*>(data);
    u16 dest_port = __builtin_bswap16(header->dest_port);
    u16 src_port = __builtin_bswap16(header->src_port);

    hal::ScopedLock lock(g_udp_lock);
    for (usize i = 0; i < g_udp_socket_count; i++) {
        // Simple port-based dispatch
        (void)dev; (void)src_ip; (void)src_port; (void)dest_port;
        // g_udp_sockets[i]->handle_incoming(src_ip, src_port, (u8*)data + sizeof(UDPHeader), size - sizeof(UDPHeader));
    }
}

bool UDP::send_packet(NetDevice* dev, u32 dest_ip, u16 src_port, u16 dest_port, const void* data, usize size) {
    (void)dev; (void)dest_ip; (void)src_port; (void)dest_port; (void)data; (void)size;
    // Call IPv4::send_packet with UDP payload
    return true;
}

} // namespace acos::net
