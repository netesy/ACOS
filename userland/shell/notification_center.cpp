#include "notification_center.h"
#include <userland/gui/theme.h>

namespace acos::shell {

NotificationCenter::NotificationCenter() : m_count(0) {
    m_rect = {590, 50, 200, 400};
    set_visible(false);
}

void NotificationCenter::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w),
                        static_cast<u32>(m_rect.h),
                        gui::g_current_theme.glass_bg, (u8)((gui::g_current_theme.glass_bg >> 24) & 0xFF));

    renderer->draw_rounded_rect(static_cast<u32>(m_rect.x),
                               static_cast<u32>(m_rect.y),
                               static_cast<u32>(m_rect.w),
                               static_cast<u32>(m_rect.h),
                               gui::g_current_theme.widget_radius,
                               gui::g_current_theme.border);

    renderer->draw_text("Notifications", (u32)m_rect.x + 10, (u32)m_rect.y + 10, gui::g_current_theme.secondary,
                       acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);
}

void NotificationCenter::post_notification(const char* title, const char* message) {
    if (m_count < 16) {
        m_queue[m_count++] = {title, message, 0};
    }
}

} // namespace acos::shell
