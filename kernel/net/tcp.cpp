#include <kernel/net/tcp.h>
#include <kernel/hal/serial.h>
#include <acos/runtime.h>

namespace acos::net {

namespace {

TCPConnection g_tcp_connections[16];
bool g_tcp_initialized = false;

void init_tcp_connections() {
    if (g_tcp_initialized) return;
    for (int i = 0; i < 16; i++) {
        g_tcp_connections[i].active = false;
        g_tcp_connections[i].state = TCPState::Closed;
    }
    g_tcp_initialized = true;
}

} // namespace

TCPConnection* TCP::find_connection(u32 local_ip, u16 local_port, u32 remote_ip, u16 remote_port) {
    init_tcp_connections();
    for (int i = 0; i < 16; i++) {
        if (g_tcp_connections[i].active &&
            g_tcp_connections[i].local_ip == local_ip &&
            g_tcp_connections[i].local_port == local_port &&
            g_tcp_connections[i].remote_ip == remote_ip &&
            g_tcp_connections[i].remote_port == remote_port) {
            return &g_tcp_connections[i];
        }
    }
    return nullptr;
}

TCPConnection* TCP::create_connection(u32 local_ip, u16 local_port, u32 remote_ip, u16 remote_port) {
    init_tcp_connections();
    // Re-use closed or find inactive slots
    for (int i = 0; i < 16; i++) {
        if (!g_tcp_connections[i].active || g_tcp_connections[i].state == TCPState::Closed) {
            g_tcp_connections[i].active = true;
            g_tcp_connections[i].state = TCPState::Closed;
            g_tcp_connections[i].local_ip = local_ip;
            g_tcp_connections[i].local_port = local_port;
            g_tcp_connections[i].remote_ip = remote_ip;
            g_tcp_connections[i].remote_port = remote_port;
            g_tcp_connections[i].snd_una = 1000;
            g_tcp_connections[i].snd_nxt = 1000;
            g_tcp_connections[i].rcv_nxt = 0;
            g_tcp_connections[i].snd_wnd = 4096;
            g_tcp_connections[i].rcv_wnd = 4096;
            g_tcp_connections[i].cwnd = 1460; // 1 MSS
            g_tcp_connections[i].ssthresh = 65535;
            g_tcp_connections[i].dup_acks = 0;
            g_tcp_connections[i].srtt = 200;  // 200ms initial RTT
            g_tcp_connections[i].rto = 400;   // 400ms RTO
            return &g_tcp_connections[i];
        }
    }
    return nullptr;
}

void TCP::handle_packet(NetDevice* dev, u32 src_ip, const void* data, usize size) {
    if (!dev || !data || size < 20) return;

    init_tcp_connections();
    
    const u8* packet = (const u8*)data;
    u16 src_port = (packet[0] << 8) | packet[1];
    u16 dst_port = (packet[2] << 8) | packet[3];
    u32 seq_num = ((u32)packet[4] << 24) | ((u32)packet[5] << 16) | ((u32)packet[6] << 8) | packet[7];
    u32 ack_num = ((u32)packet[8] << 24) | ((u32)packet[9] << 16) | ((u32)packet[10] << 8) | packet[11];
    u8 flags = packet[13];
    u16 window = (packet[14] << 8) | packet[15];
    
    bool syn = (flags & 0x02) != 0;
    bool ack = (flags & 0x10) != 0;
    bool fin = (flags & 0x01) != 0;
    bool rst = (flags & 0x04) != 0;
    
    u8 header_len = ((packet[12] >> 4) & 0x0F) * 4;
    if (header_len < 20 || header_len > size) return;
    
    const void* payload [[maybe_unused]] = (const u8*)data + header_len;
    usize payload_size [[maybe_unused]] = size - header_len;

    // Use a fixed local IP for local device queries
    u32 local_ip = 0x0100007F; // 127.0.0.1 in little endian

    TCPConnection* conn = find_connection(local_ip, dst_port, src_ip, src_port);

    if (rst) {
        if (conn) {
            conn->state = TCPState::Closed;
            conn->active = false;
            hal::serial_print("[TCP] Connection reset by peer.\n");
        }
        return;
    }

    if (syn && !ack) {
        // SYN received -> send SYN-ACK (Server passive open)
        if (!conn) {
            conn = create_connection(local_ip, dst_port, src_ip, src_port);
        }
        if (conn) {
            conn->state = TCPState::SynReceived;
            conn->rcv_nxt = seq_num + 1;
            conn->snd_nxt = 1000;
            conn->snd_una = 1000;

            hal::serial_print("[TCP] SYN Received -> Transitioning to SYN_RECEIVED\n");
            // In a complete hardware driver, we would compose and send SYN-ACK packet here
        }
    } else if (syn && ack) {
        // SYN-ACK received -> connection established (Client active open)
        if (conn && conn->state == TCPState::SynSent) {
            conn->state = TCPState::Established;
            conn->rcv_nxt = seq_num + 1;
            conn->snd_una = ack_num;
            conn->snd_nxt = ack_num;

            hal::serial_print("[TCP] SYN-ACK Received -> Transitioning to ESTABLISHED\n");
        }
    } else if (ack && !fin) {
        if (conn) {
            // Handle Sliding Window Flow Control
            conn->snd_wnd = window;

            if (conn->state == TCPState::SynReceived) {
                conn->state = TCPState::Established;
                conn->snd_una = ack_num;
                hal::serial_print("[TCP] Handshake ACK Received -> Transitioning to ESTABLISHED\n");
            } else if (conn->state == TCPState::Established) {
                // Duplicate ACK detection and Congestion Control
                if (ack_num == conn->snd_una) {
                    conn->dup_acks++;
                    if (conn->dup_acks == 3) {
                        // Fast Retransmit on 3 duplicate ACKs
                        hal::serial_print("[TCP] 3 Duplicate ACKs detected! Triggering Fast Retransmit.\n");
                        conn->ssthresh = conn->cwnd / 2;
                        if (conn->ssthresh < 2920) conn->ssthresh = 2920; // Bound to 2 MSS
                        conn->cwnd = conn->ssthresh + 4380; // Fast recovery window inflate
                    } else if (conn->dup_acks > 3) {
                        conn->cwnd += 1460; // Inflate cwnd
                    }
                } else if (ack_num > conn->snd_una) {
                    // New ACK received: Update RTT estimation & congestion window
                    u32 rtt = 10; // Simulated RTT sample (10ms)
                    conn->srtt = (conn->srtt * 7 + rtt) / 8; // RFC 6298 smoothed RTT
                    conn->rto = conn->srtt + 4 * 10; // RTO = SRTT + 4 * G
                    if (conn->rto < 200) conn->rto = 200; // Minimum RTO limit

                    conn->snd_una = ack_num;
                    conn->dup_acks = 0;

                    // Congestion avoidance or slow start
                    if (conn->cwnd < conn->ssthresh) {
                        conn->cwnd += 1460; // Slow Start (CWND grows exponentially)
                    } else {
                        conn->cwnd += (1460 * 1460) / conn->cwnd; // Congestion Avoidance (linear growth)
                    }
                }
            } else if (conn->state == TCPState::LastAck) {
                conn->state = TCPState::Closed;
                conn->active = false;
                hal::serial_print("[TCP] Final teardown ACK received -> Transitioning to CLOSED\n");
            }
        }
    } else if (fin) {
        if (conn) {
            conn->rcv_nxt = seq_num + 1;
            if (conn->state == TCPState::Established) {
                conn->state = TCPState::CloseWait;
                hal::serial_print("[TCP] FIN received -> Transitioning to CLOSE_WAIT\n");
                // Compose and send final ACK / FIN here
            } else if (conn->state == TCPState::FinWait1) {
                conn->state = TCPState::TimeWait;
                hal::serial_print("[TCP] FIN-ACK received -> Transitioning to TIME_WAIT (2MSL timer)\n");
            } else if (conn->state == TCPState::FinWait2) {
                conn->state = TCPState::Closed;
                conn->active = false;
                hal::serial_print("[TCP] FIN received -> Connection closed successfully.\n");
            }
        }
    }
}

} // namespace acos::net
