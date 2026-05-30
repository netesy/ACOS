#pragma once
#include <acos/types.h>
#include <kernel/ipc/message.h>
#include <kernel/hal/spinlock.h>
#include <kernel/scheduler/thread.h>

namespace acos::ipc {

class Channel {
public:
    static constexpr usize MAX_MESSAGES = 16;
    static constexpr usize MAX_WAITERS = 8;

    Channel();
    bool send(const Message& msg);
    bool receive(Message& msg, bool block = true);

    u64 id() const { return m_id; }

private:
    u64 m_id;
    hal::SpinLock m_lock;

    Message m_buffer[MAX_MESSAGES];
    usize m_head;
    usize m_tail;
    usize m_count;

    scheduler::Thread* m_readers[MAX_WAITERS];
    usize m_reader_count;
};

} // namespace acos::ipc
