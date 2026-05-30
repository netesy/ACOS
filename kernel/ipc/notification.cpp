#include <kernel/ipc/notification.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::ipc {

static u64 g_next_notification_id = 1;

Notification::Notification() : m_signaled(false), m_wait_count(0) {
    m_id = g_next_notification_id++;
    for(usize i=0; i<16; i++) m_waiting_threads[i] = nullptr;
}

void Notification::signal() {
    hal::ScopedLock lock(m_lock);
    m_signaled = true;

    // Wake all waiting threads
    for (usize i = 0; i < m_wait_count; i++) {
        scheduler::wake_thread(m_waiting_threads[i]);
        m_waiting_threads[i] = nullptr;
    }
    m_wait_count = 0;
}

void Notification::wait() {
    m_lock.lock();
    if (m_signaled) {
        m_lock.unlock();
        return;
    }

    scheduler::Thread* current = scheduler::current_thread();
    if (m_wait_count < 16) {
        m_waiting_threads[m_wait_count++] = current;
        m_lock.unlock();

        scheduler::block_thread(current);

        // After waking up, we loop back or return
    } else {
        m_lock.unlock();
    }
}

void Notification::reset() {
    hal::ScopedLock lock(m_lock);
    m_signaled = false;
}

} // namespace acos::ipc
