#include <kernel/input/input_queue.h>
#include <kernel/input/input_manager.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::input {

InputQueue::InputQueue() : m_head(0), m_tail(0), m_count(0), m_wait_count(0) {
    for (usize i = 0; i < 16; i++) {
        m_waiting_threads[i] = nullptr;
    }
}

InputQueue::~InputQueue() {
    InputManager::unregister_queue(this);

    m_lock.lock();
    for (usize i = 0; i < m_wait_count; i++) {
        if (m_waiting_threads[i]) {
            scheduler::wake_thread(m_waiting_threads[i]);
        }
    }
    m_lock.unlock();
}

void InputQueue::push_event(const InputEvent& event) {
    hal::ScopedLock lock(m_lock);
    if (m_count < QUEUE_SIZE) {
        m_events[m_tail] = event;
        m_tail = (m_tail + 1) % QUEUE_SIZE;
        m_count++;

        // Wake one waiting thread
        if (m_wait_count > 0) {
            scheduler::wake_thread(m_waiting_threads[0]);
            for (usize i = 0; i < m_wait_count - 1; i++) {
                m_waiting_threads[i] = m_waiting_threads[i + 1];
            }
            m_waiting_threads[m_wait_count - 1] = nullptr;
            m_wait_count--;
        }
    }
}

bool InputQueue::pop_event(InputEvent& event, bool block) {
    m_lock.lock();
    while (m_count == 0) {
        if (!block) {
            m_lock.unlock();
            return false;
        }

        scheduler::Thread* current = scheduler::current_thread();
        if (m_wait_count < 16) {
            // Set thread state to Blocked BEFORE releasing the lock to eliminate lost wakeup race condition.
            current->state = scheduler::ThreadState::Blocked;
            m_waiting_threads[m_wait_count++] = current;
            m_lock.unlock();
            scheduler::schedule();
            m_lock.lock();
        } else {
            m_lock.unlock();
            return false;
        }
    }

    event = m_events[m_head];
    m_head = (m_head + 1) % QUEUE_SIZE;
    m_count--;
    m_lock.unlock();
    return true;
}

} // namespace acos::input
