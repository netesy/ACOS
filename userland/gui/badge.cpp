#include "badge.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Badge::Badge(const char* text) : m_text(text) {
    m_rect.w = 20;
    m_rect.h = 20;
}

void Badge::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer || !m_text) return;

    renderer->fill_circle(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2, m_rect.w / 2, g_current_theme.error);
    renderer->draw_text(m_text, m_rect.x + 6, m_rect.y + 4, 0xFFFFFFFF);
}

} // namespace acos::gui
