#include "notification_center.h"
#include <userland/gui/theme.h>

namespace acos::shell {

NotificationCenter::NotificationCenter() : m_count(0) {
    m_rect = {600, 0, 200, 600}; // Right sidebar
}

void NotificationCenter::draw(u32* buffer, u32 pitch) {
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = 0x88000000; // Semi-transparent black
        }
    }
}

void NotificationCenter::post_notification(const char* title, const char* message) {
    if (m_count < 16) {
        m_queue[m_count++] = {title, message, 0};
    }
}

} // namespace acos::shell
