#include "launcher.h"
#include <userland/gui/theme.h>

namespace acos::shell {

Launcher::Launcher() {
    m_rect = {10, 10, 200, 300};
    m_visible = false;
}

void Launcher::draw(acos::graphics::Renderer* renderer) {
    if (!m_visible || !renderer) return;

    // Glassmorphic launcher
    renderer->blend_rect(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w),
                        static_cast<u32>(m_rect.h),
                        gui::g_current_theme.glass_bg, (u8)((gui::g_current_theme.glass_bg >> 24) & 0xFF));

    renderer->draw_rounded_rect(static_cast<u32>(m_rect.x),
                               static_cast<u32>(m_rect.y),
                               static_cast<u32>(m_rect.w),
                               static_cast<u32>(m_rect.h),
                               gui::g_current_theme.window_radius,
                               gui::g_current_theme.border);

    renderer->draw_text("Applications", (u32)m_rect.x + 10, (u32)m_rect.y + 10, gui::g_current_theme.primary,
                       acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);
}

} // namespace acos::shell
