#include <kernel/net/socket.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/hal/spinlock.h>
#include <kernel/hal/serial.h>

namespace acos::net {

namespace {

class LocalSocket final : public Socket {
public:
    LocalSocket() : m_bound_ip(0), m_bound_port(0), m_peer_ip(0), m_peer_port(0),
                    m_size(0), m_closed(false), m_peer_socket(nullptr) {}

    void initialize(i32 domain, i32 type, i32 protocol) {
        m_domain = domain;
        m_type = type;
        m_protocol = protocol;
        m_bound_ip = 0;
        m_bound_port = 0;
        m_peer_ip = 0;
        m_peer_port = 0;
        m_size = 0;
        m_closed = false;
        m_peer_socket = nullptr;
    }

    i32 bind(u32 ip, u16 port) override {
        hal::ScopedLock lock(m_lock);
        if (m_closed) {
            return -1;
        }
        m_bound_ip = ip;
        m_bound_port = port;
        return 0;
    }

    i32 listen(int backlog) override {
        hal::ScopedLock lock(m_lock);
        if (m_closed || backlog < 0) {
            return -1;
        }
        return 0;
    }

    i32 connect(u32 ip, u16 port) override;

    i32 send(const void* buffer, usize size) override {
        hal::ScopedLock lock(m_lock);
        if (m_closed || !buffer) {
            return -1;
        }

        // Fast-path: if loopback connected peer is registered, bypass network card!
        if (m_peer_socket) {
            return m_peer_socket->enqueue_loopback_data(buffer, size);
        }

        // Standard/fallback local buffering
        return enqueue_local_data(buffer, size);
    }

    i32 recv(void* buffer, usize size) override {
        hal::ScopedLock lock(m_lock);
        if (m_closed || !buffer) {
            return -1;
        }

        const usize readable = (m_size < size) ? m_size : size;
        memcpy(buffer, m_buffer, readable);
        if (readable < m_size) {
            const usize remaining = m_size - readable;
            for (usize i = 0; i < remaining; ++i) {
                m_buffer[i] = m_buffer[i + readable];
            }
        }
        m_size -= readable;
        return static_cast<i32>(readable);
    }

    void close() override {
        hal::ScopedLock lock(m_lock);
        m_closed = true;
        m_size = 0;
        if (m_peer_socket) {
            m_peer_socket->disconnect_peer();
            m_peer_socket = nullptr;
        }
    }

    bool accepts_udp(u16 port) const {
        return !m_closed && m_bound_port == port;
    }

    bool enqueue_datagram(u32 src_ip, u16 src_port, const void* data, usize size) {
        hal::ScopedLock lock(m_lock);
        if (!data || size > kBufferSize) {
            return false;
        }
        m_peer_ip = src_ip;
        m_peer_port = src_port;
        memcpy(m_buffer, data, size);
        m_size = size;
        return true;
    }

    // Direct loopback data delivery
    i32 enqueue_loopback_data(const void* data, usize size) {
        hal::ScopedLock lock(m_lock);
        if (m_closed || !data) return -1;

        const usize space_available = kBufferSize - m_size;
        const usize writable = (size < space_available) ? size : space_available;
        if (writable > 0) {
            memcpy(m_buffer + m_size, data, writable);
            m_size += writable;
            return static_cast<i32>(writable);
        }
        return 0; // Buffer full
    }

    // Fallback data delivery
    i32 enqueue_local_data(const void* data, usize size) {
        const usize space_available = kBufferSize - m_size;
        const usize writable = (size < space_available) ? size : space_available;
        if (writable > 0) {
            memcpy(m_buffer + m_size, data, writable);
            m_size += writable;
            return static_cast<i32>(writable);
        }
        return 0;
    }

    void disconnect_peer() {
        hal::ScopedLock lock(m_lock);
        m_peer_socket = nullptr;
    }

    u16 bound_port() const { return m_bound_port; }
    u32 bound_ip() const { return m_bound_ip; }

private:
    static constexpr usize kBufferSize = 2048;

    i32 m_domain;
    i32 m_type;
    i32 m_protocol;
    u32 m_bound_ip;
    u16 m_bound_port;
    u32 m_peer_ip;
    u16 m_peer_port;
    u8 m_buffer[kBufferSize];
    usize m_size;
    bool m_closed;

    hal::SpinLock m_lock;
    LocalSocket* m_peer_socket;
};

static LocalSocket g_sockets[64];
static bool g_socket_used[64];

i32 LocalSocket::connect(u32 ip, u16 port) {
    hal::ScopedLock lock(m_lock);
    if (m_closed) {
        return -1;
    }
    m_peer_ip = ip;
    m_peer_port = port;

    // Loopback Routing Optimization (127.0.0.1)
    if (ip == 0x0100007F || ip == 0x7F000001) {
        // Search for a matching bound socket
        for (usize i = 0; i < 64; i++) {
            if (g_socket_used[i] && &g_sockets[i] != this && g_sockets[i].bound_port() == port) {
                m_peer_socket = &g_sockets[i];
                g_sockets[i].m_peer_socket = this;
                acos::hal::serial_print("[SOCKET] Loopback direct IPC link established on port: ");
                acos::hal::serial_print_hex(port);
                acos::hal::serial_print("\n");
                return 0;
            }
        }
    }
    return 0;
}

} // namespace

Socket* Socket::create(i32 domain, i32 type, i32 protocol) {
    for (usize i = 0; i < 64; ++i) {
        if (!g_socket_used[i]) {
            g_socket_used[i] = true;
            g_sockets[i].initialize(domain, type, protocol);
            return &g_sockets[i];
        }
    }
    return nullptr;
}

bool Socket::deliver_udp(u32 src_ip, u16 src_port, u16 dest_port, const void* data, usize size) {
    for (usize i = 0; i < 64; ++i) {
        if (g_socket_used[i] && g_sockets[i].accepts_udp(dest_port)) {
            return g_sockets[i].enqueue_datagram(src_ip, src_port, data, size);
        }
    }
    return false;
}

} // namespace acos::net
