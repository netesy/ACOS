#include "toolbutton.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ToolButton::ToolButton(const char* label) : Button(label) {
    m_rect.w = 32;
    m_rect.h = 32;
}

void ToolButton::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    if (m_state == WidgetState::Hovered) {
        renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 150);
        renderer->draw_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.primary);
    } else if (m_state == WidgetState::Pressed) {
        renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.primary, 100);
    }

    // Centered label (usually an icon char or short text)
    renderer->draw_text(label(), m_rect.x + 8, m_rect.y + 8, g_current_theme.text);
}

} // namespace acos::gui
