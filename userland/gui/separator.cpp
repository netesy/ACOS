#include "separator.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Separator::Separator(Orientation orient) : m_orientation(orient) {
    if (m_orientation == Orientation::Horizontal) {
        m_rect.h = 1;
        m_rect.w = 100;
    } else {
        m_rect.w = 1;
        m_rect.h = 100;
    }
}

void Separator::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;
    if (m_orientation == Orientation::Horizontal) {
        renderer->draw_line(m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y, g_current_theme.border);
    } else {
        renderer->draw_line(m_rect.x, m_rect.y, m_rect.x, m_rect.y + m_rect.h, g_current_theme.border);
    }
}

} // namespace acos::gui
