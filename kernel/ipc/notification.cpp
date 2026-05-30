#include <kernel/ipc/notification.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::ipc {

static u64 g_next_notification_id = 1;

Notification::Notification() : m_signaled(false) {
    m_id = g_next_notification_id++;
}

void Notification::signal() {
    m_signaled = true;
    // Wake up threads waiting on this notification would go here.
    // For Phase 4, we provide the infrastructure.
}

void Notification::wait() {
    while (!m_signaled) {
        // block_thread(current_thread());
        __asm__("hlt");
    }
}

void Notification::reset() {
    m_signaled = false;
}

} // namespace acos::ipc
