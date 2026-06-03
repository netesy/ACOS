#include "groupbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

GroupBox::GroupBox(const char* title) : m_title(title) {
    m_rect = {0, 0, 100, 100};
}

void GroupBox::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Draw border
    renderer->draw_rounded_rect(m_rect.x, m_rect.y + 8, m_rect.w, m_rect.h - 8, 4, g_current_theme.border);

    // Draw title
    if (m_title) {
        renderer->blend_rect(m_rect.x + 10, m_rect.y, 80, 16, g_current_theme.background, 255);
        renderer->draw_text(m_title, m_rect.x + 15, m_rect.y, g_current_theme.primary, acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);
    }

    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i]) m_children[i]->draw(renderer);
    }
}

} // namespace acos::gui
