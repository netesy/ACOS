#include "toolbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ToolBar::ToolBar() {
    m_rect.h = 40;
}

void ToolBar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 200);
    renderer->draw_line(m_rect.x, m_rect.y + m_rect.h, m_rect.x + m_rect.w, m_rect.y + m_rect.h, g_current_theme.border);

    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i]) m_children[i]->draw(renderer);
    }
}

} // namespace acos::gui
