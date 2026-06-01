#pragma once
#include <acos/types.h>

namespace acos::net {

enum class SocketType {
    Stream,
    Dgram,
    Raw
};

class Socket {
public:
    virtual ~Socket() = default;

    static Socket* create(i32 domain, i32 type, i32 protocol);
    static bool deliver_udp(u32 src_ip, u16 src_port, u16 dest_port, const void* data, usize size);

    virtual i32 bind(u32 ip, u16 port) = 0;
    virtual i32 listen(int backlog) = 0;
    virtual i32 connect(u32 ip, u16 port) = 0;
    virtual i32 send(const void* buffer, usize size) = 0;
    virtual i32 recv(void* buffer, usize size) = 0;
    virtual void close() = 0;
};

} // namespace acos::net
