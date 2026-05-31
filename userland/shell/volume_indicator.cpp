#include "volume_indicator.h"
#include <userland/gui/theme.h>

namespace acos::shell {

VolumeIndicator::VolumeIndicator() : m_volume(50) {
    m_rect = {750, 5, 40, 30};
}

void VolumeIndicator::draw(u32* buffer, u32 pitch) {
    // Draw simple volume icon/bar
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = gui::g_current_theme.accent;
        }
    }
}

} // namespace acos::shell
