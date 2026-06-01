#include <kernel/net/socket.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::net {

namespace {

class LocalSocket final : public Socket {
public:
    LocalSocket() : m_bound_ip(0), m_bound_port(0), m_peer_ip(0), m_peer_port(0),
                    m_size(0), m_closed(false) {}

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
    }

    i32 bind(u32 ip, u16 port) override {
        if (m_closed) {
            return -1;
        }
        m_bound_ip = ip;
        m_bound_port = port;
        return 0;
    }

    i32 listen(int backlog) override {
        if (m_closed || backlog < 0) {
            return -1;
        }
        return 0;
    }

    i32 connect(u32 ip, u16 port) override {
        if (m_closed) {
            return -1;
        }
        m_peer_ip = ip;
        m_peer_port = port;
        return 0;
    }

    i32 send(const void* buffer, usize size) override {
        if (m_closed || !buffer) {
            return -1;
        }

        const usize writable = (size < kBufferSize) ? size : kBufferSize;
        memcpy(m_buffer, buffer, writable);
        m_size = writable;
        return static_cast<i32>(writable);
    }

    i32 recv(void* buffer, usize size) override {
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
        m_closed = true;
        m_size = 0;
    }

    bool accepts_udp(u16 port) const {
        return !m_closed && m_bound_port == port;
    }

    bool enqueue_datagram(u32 src_ip, u16 src_port, const void* data, usize size) {
        if (!data || size > kBufferSize) {
            return false;
        }
        m_peer_ip = src_ip;
        m_peer_port = src_port;
        memcpy(m_buffer, data, size);
        m_size = size;
        return true;
    }

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
};

static LocalSocket g_sockets[64];
static bool g_socket_used[64];

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
