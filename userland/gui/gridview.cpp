#include "gridview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

GridView::GridView(u32 columns) : m_columns(columns), m_cell_count(0) {
    m_rect.w = 400;
    m_rect.h = 300;
    for (int i = 0; i < 8; i++) m_headers[i] = nullptr;
}

GridView::~GridView() {}

void GridView::set_header(u32 index, const char* title) {
    if (index < 8) m_headers[index] = title;
}

void GridView::add_cell(const char* text) {
    if (m_cell_count < 256) m_cells[m_cell_count++] = text;
}

void GridView::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    draw_shadow(renderer);
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 150);
    renderer->draw_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.border);

    i32 col_w = m_rect.w / (m_columns ? m_columns : 1);
    i32 row_h = 24;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, row_h, g_current_theme.surface, 200);
    for (u32 i = 0; i < m_columns; i++) {
        if (m_headers[i]) {
            renderer->draw_text(m_headers[i], m_rect.x + i * col_w + 5, m_rect.y + 4, g_current_theme.primary, acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);
        }
        if (i > 0) renderer->draw_line(m_rect.x + i * col_w, m_rect.y, m_rect.x + i * col_w, m_rect.y + m_rect.h, g_current_theme.border);
    }
    renderer->draw_line(m_rect.x, m_rect.y + row_h, m_rect.x + m_rect.w, m_rect.y + row_h, g_current_theme.border);

    for (u32 i = 0; i < m_cell_count; i++) {
        u32 row = i / m_columns;
        u32 col = i % m_columns;
        i32 cy = m_rect.y + row_h + row * row_h;
        if (cy + row_h > m_rect.y + m_rect.h) break;

        renderer->draw_text(m_cells[i], m_rect.x + col * col_w + 5, cy + 4, g_current_theme.text);
        if (col == 0) renderer->draw_line(m_rect.x, cy + row_h, m_rect.x + m_rect.w, cy + row_h, (u32)(g_current_theme.border & 0x00FFFFFF) | 0x22000000);
    }
}

void GridView::handle_event(const acos::input::InputEvent& event) {
    (void)event;
}

} // namespace acos::gui
