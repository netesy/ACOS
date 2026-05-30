#include <kernel/net/tcp.h>
#include <kernel/net/tcp_socket.h>
#include <kernel/hal/spinlock.h>

namespace acos::net {

static TCPSocket* g_tcp_sockets[128];
static usize g_tcp_socket_count = 0;
static hal::SpinLock g_tcp_lock;

void TCP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    if (size < sizeof(TCPHeader)) return;
    const TCPHeader* header = reinterpret_cast<const TCPHeader*>(data);
    (void)dev; (void)src_ip; (void)header;

    hal::ScopedLock lock(g_tcp_lock);
    for (usize i = 0; i < g_tcp_socket_count; i++) {
        // Dispatch to appropriate TCPSocket based on ports and IP
    }
}

} // namespace acos::net
