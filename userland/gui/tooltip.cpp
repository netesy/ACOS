#include "tooltip.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Tooltip::Tooltip() : m_text(nullptr) {
    m_rect.w = 120;
    m_rect.h = 24;
    m_elevation = 16;
}

void Tooltip::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer || !m_text) return;

    draw_shadow(renderer);
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF000000, 230);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.primary);
    renderer->draw_text(m_text, m_rect.x + 8, m_rect.y + 4, 0xFFFFFFFF);
}

} // namespace acos::gui
