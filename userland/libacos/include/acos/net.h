#pragma once
#include <acos/types.h>

namespace acos::net {

class Socket {
public:
    Socket();
    virtual ~Socket();

    i32 bind(const char* ip, u16 port);
    i32 connect(const char* ip, u16 port);
    i32 send(const void* buf, usize size);
    i32 receive(void* buf, usize size);
    i32 set_option(u32 level, u32 option, const void* val, usize len);
    i32 set_window_scale(u8 scale_shift);
    i32 close();

    u64 handle() const { return m_handle; }
protected:
    u64 m_handle;
};

enum class TCPState {
    Closed,
    SynSent,
    Established,
    FinWait,
    ClosedWait
};

struct TCPOptions {
    u16 mss;
    u8 window_scale;
    bool timestamps;
};

class TCPSocket : public Socket {
public:
    TCPSocket();

    i32 connect_with_options(const char* ip, u16 port, const TCPOptions& opts);
    TCPState state() const { return m_state; }
    u32 congestion_window() const { return m_cwnd; }

private:
    TCPState m_state;
    TCPOptions m_options;
    u32 m_cwnd;
};

class UDPSocket : public Socket {
public:
    UDPSocket();
};

} // namespace acos::net
