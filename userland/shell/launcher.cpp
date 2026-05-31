#include "launcher.h"
#include <userland/gui/theme.h>
#include <userland/pkg/package_database.h>

namespace acos::shell {

Launcher::Launcher() : m_active(false) {
    m_rect = {0, 0, 300, 400};
}

void Launcher::draw(u32* buffer, u32 pitch) {
    if (!m_active) return;
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = gui::g_current_theme.background;
        }
    }
    // Dynamic application discovery from PackageDatabase would happen here
}

void Launcher::show() { m_active = true; }
void Launcher::hide() { m_active = false; }

} // namespace acos::shell
