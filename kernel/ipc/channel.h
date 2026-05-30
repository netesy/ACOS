#pragma once
#include <acos/types.h>
#include <kernel/ipc/message.h>

namespace acos::ipc {

class Channel {
public:
    static constexpr usize MAX_MESSAGES = 16;

    Channel();
    bool send(const Message& msg);
    bool receive(Message& msg);

    u64 id() const { return m_id; }
    u64 owner() const { return m_owner; }

private:
    u64 m_id;
    u64 m_owner;
    Message m_buffer[MAX_MESSAGES];
    usize m_head;
    usize m_tail;
    usize m_count;
};

} // namespace acos::ipc
