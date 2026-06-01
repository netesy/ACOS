#include "launcher.h"
#include <userland/gui/theme.h>

namespace acos::shell {

Launcher::Launcher() : m_active(false) {
    m_rect = {0, 0, 300, 400};
}

void Launcher::draw(acos::graphics::Renderer* renderer) {
    if (!m_active || !renderer) {
        return;
    }

    renderer->fill_rect(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w),
                        static_cast<u32>(m_rect.h),
                        gui::g_current_theme.background);
    renderer->draw_border(static_cast<u32>(m_rect.x),
                          static_cast<u32>(m_rect.y),
                          static_cast<u32>(m_rect.w),
                          static_cast<u32>(m_rect.h),
                          gui::g_current_theme.border,
                          1);
    renderer->draw_text("Applications",
                        static_cast<u32>(m_rect.x + 16),
                        static_cast<u32>(m_rect.y + 16),
                        gui::g_current_theme.text);
}

void Launcher::show() { m_active = true; }
void Launcher::hide() { m_active = false; }

} // namespace acos::shell
