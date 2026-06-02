#include "panel.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Panel::Panel() : m_bg_color(g_current_theme.surface), m_is_glass(false) {
    m_rect = {0, 0, 100, 100};
}

Panel::~Panel() {}

void Panel::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    if (m_is_glass) {
        renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.glass_bg, (u8)((g_current_theme.glass_bg >> 24) & 0xFF));
    } else {
        renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, m_bg_color);
    }

    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, g_current_theme.border);

    // Draw children
    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i] && m_children[i]->is_visible()) {
            m_children[i]->draw(renderer);
        }
    }
}

} // namespace acos::gui
