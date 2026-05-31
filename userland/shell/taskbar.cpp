#include "taskbar.h"
#include <userland/gui/theme.h>

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 800, 40}; // Bottom bar
}

void Taskbar::draw(u32* buffer, u32 pitch) {
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = gui::g_current_theme.widget_bg;
        }
    }
}

void Taskbar::update_clock() {
    // In a real implementation, get system time
}

} // namespace acos::shell
