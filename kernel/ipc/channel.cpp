#include <kernel/ipc/channel.h>

namespace acos::ipc {

static u64 g_next_channel_id = 1;

Channel::Channel() : m_head(0), m_tail(0), m_count(0) {
    m_id = g_next_channel_id++;
}

bool Channel::send(const Message& msg) {
    if (m_count >= MAX_MESSAGES) {
        return false;
    }

    m_buffer[m_tail] = msg;
    m_tail = (m_tail + 1) % MAX_MESSAGES;
    m_count++;

    return true;
}

bool Channel::receive(Message& msg) {
    if (m_count == 0) {
        return false;
    }

    msg = m_buffer[m_head];
    m_head = (m_head + 1) % MAX_MESSAGES;
    m_count--;

    return true;
}

} // namespace acos::ipc
