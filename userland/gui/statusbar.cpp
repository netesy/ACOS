#include "statusbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

StatusBar::StatusBar() : m_text("Ready") {
    m_rect.h = 24;
}

void StatusBar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 220);
    renderer->draw_line(m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y, g_current_theme.border);
    renderer->draw_text(m_text, m_rect.x + 10, m_rect.y + 4, g_current_theme.text_secondary, acos::graphics::Font::Alignment::Left);
}

} // namespace acos::gui
