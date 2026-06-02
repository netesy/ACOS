#include "volume_indicator.h"
#include <userland/gui/theme.h>

namespace acos::shell {

VolumeIndicator::VolumeIndicator() : m_volume(50) {
    m_rect = {750, 5, 40, 30};
}

void VolumeIndicator::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) {
        return;
    }

    const u32 x = static_cast<u32>(m_rect.x);
    const u32 y = static_cast<u32>(m_rect.y);
    const u32 h = static_cast<u32>(m_rect.h);
    const u32 bar_width = (m_volume > 100 ? 100 : m_volume) / 4;

    renderer->draw_rect(x, y + 8, 8, 14, gui::g_current_theme.text);
    renderer->fill_rect(x + 10, y + 6, bar_width, h - 12, gui::g_current_theme.primary);
    renderer->draw_border(x + 10, y + 6, 25, h - 12, gui::g_current_theme.border, 1);
}

} // namespace acos::shell
