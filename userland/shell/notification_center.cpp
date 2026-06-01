#include "notification_center.h"
#include <userland/gui/theme.h>

namespace acos::shell {

NotificationCenter::NotificationCenter() : m_count(0) {
    m_rect = {600, 0, 200, 600};
}

void NotificationCenter::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) {
        return;
    }

    renderer->blend_rect(static_cast<u32>(m_rect.x),
                         static_cast<u32>(m_rect.y),
                         static_cast<u32>(m_rect.w),
                         static_cast<u32>(m_rect.h),
                         0xFF000000,
                         136);

    u32 y = static_cast<u32>(m_rect.y + 12);
    for (usize i = 0; i < m_count; ++i) {
        renderer->draw_text(m_queue[i].title, static_cast<u32>(m_rect.x + 12), y, gui::g_current_theme.text);
        y += 12;
        renderer->draw_text(m_queue[i].message, static_cast<u32>(m_rect.x + 12), y, gui::g_current_theme.text_secondary);
        y += 24;
    }
}

void NotificationCenter::post_notification(const char* title, const char* message) {
    if (m_count < 16) {
        m_queue[m_count++] = {title, message, 0};
    }
}

} // namespace acos::shell
