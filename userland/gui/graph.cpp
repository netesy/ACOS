#include "graph.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Graph::Graph() : m_count(0) {
    m_rect.w = 200;
    m_rect.h = 100;
    for(int i=0; i<64; i++) m_data[i] = 0;
}

void Graph::add_value(float val) {
    if (m_count < 64) m_data[m_count++] = val;
    else {
        for(int i=0; i<63; i++) m_data[i] = m_data[i+1];
        m_data[63] = val;
    }
}

void Graph::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF000000, 100);
    renderer->draw_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.border);

    if (m_count < 2) return;

    float step_x = (float)m_rect.w / (m_count - 1);
    for (u32 i = 0; i < m_count - 1; i++) {
        i32 x1 = m_rect.x + (i32)(i * step_x);
        i32 y1 = m_rect.y + m_rect.h - (i32)(m_data[i] * m_rect.h / 100.0f);
        i32 x2 = m_rect.x + (i32)((i + 1) * step_x);
        i32 y2 = m_rect.y + m_rect.h - (i32)(m_data[i+1] * m_rect.h / 100.0f);
        renderer->draw_line(x1, y1, x2, y2, g_current_theme.primary);
    }
}

} // namespace acos::gui
