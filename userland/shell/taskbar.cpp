#include "taskbar.h"
#include <userland/gui/theme.h>

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 800, 40};
    m_volume.set_position(750, 5);
}

void Taskbar::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) {
        return;
    }

    renderer->fill_rect(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w),
                        static_cast<u32>(m_rect.h),
                        gui::g_current_theme.widget_bg);
    renderer->draw_line(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.x + m_rect.w - 1),
                        static_cast<u32>(m_rect.y),
                        gui::g_current_theme.border);
    m_volume.draw(renderer);
}

void Taskbar::update_clock() {
    m_clock_str[0] = '0';
    m_clock_str[1] = '0';
    m_clock_str[2] = ':';
    m_clock_str[3] = '0';
    m_clock_str[4] = '0';
    m_clock_str[5] = '\0';
}

} // namespace acos::shell
