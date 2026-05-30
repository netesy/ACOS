#pragma once
#include <acos/types.h>
#include <kernel/hal/spinlock.h>
#include <kernel/scheduler/thread.h>

namespace acos::ipc {

class Notification {
public:
    Notification();
    void signal();
    void wait();
    void reset();

    u64 id() const { return m_id; }

private:
    u64 m_id;
    hal::SpinLock m_lock;
    bool m_signaled;

    // Wait queue (simple for now)
    scheduler::Thread* m_waiting_threads[16];
    usize m_wait_count;
};

} // namespace acos::ipc
