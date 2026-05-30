#include <kernel/ipc/channel.h>
#include <kernel/scheduler/scheduler.h>
#include <acos/runtime.h> // For memcpy

namespace acos::ipc {

static u64 g_next_channel_id = 1;

Channel::Channel() : m_head(0), m_tail(0), m_count(0), m_reader_count(0) {
    m_id = g_next_channel_id++;
    for(usize i=0; i<MAX_WAITERS; i++) m_readers[i] = nullptr;
}

bool Channel::send(const Message& msg) {
    hal::ScopedLock lock(m_lock);

    if (m_count >= MAX_MESSAGES) {
        return false;
    }

    m_buffer[m_tail] = msg;
    m_tail = (m_tail + 1) % MAX_MESSAGES;
    m_count++;

    // Wake one waiting reader
    if (m_reader_count > 0) {
        scheduler::wake_thread(m_readers[0]);
        for(usize i=0; i < m_reader_count-1; i++) m_readers[i] = m_readers[i+1];
        m_reader_count--;
    }

    return true;
}

bool Channel::receive(Message& msg, bool block) {
    while (true) {
        m_lock.lock();
        if (m_count > 0) {
            msg = m_buffer[m_head];
            m_head = (m_head + 1) % MAX_MESSAGES;
            m_count--;
            m_lock.unlock();
            return true;
        }

        if (!block) {
            m_lock.unlock();
            return false;
        }

        scheduler::Thread* current = scheduler::current_thread();
        if (m_reader_count < MAX_WAITERS) {
            m_readers[m_reader_count++] = current;
            m_lock.unlock();
            scheduler::block_thread(current);
            // After wake, loop and try to read again
        } else {
            m_lock.unlock();
            return false;
        }
    }
}

} // namespace acos::ipc
