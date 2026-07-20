#include "tableview.h"
#include "core/context.h"
#include <acos/renderer.h>

namespace acos::gui::widgets {

TableView::TableView() : m_col_count(0), m_row_count(0) {
    m_rect = {0, 0, 300, 200};
    for (int i = 0; i < 5; i++) {
        m_columns[i] = nullptr;
        for (int j = 0; j < 10; j++) {
            m_data[j][i] = nullptr;
        }
    }
}

TableView::~TableView() {}

Ref<RenderObject> TableView::create_render_object() {
    return UIContext::get().region().alloc<RenderTableView>();
}

void TableView::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rt = static_cast<RenderTableView*>(render_object.operator->());
    if (rt) {
        rt->set_columns(m_columns, m_col_count);
        rt->set_data(m_data, m_row_count, m_col_count);
    }
}

void TableView::set_columns(const char** cols, usize count) {
    m_col_count = count > 5 ? 5 : count;
    for (usize i = 0; i < m_col_count; i++) {
        m_columns[i] = cols[i];
    }
    set_paint_dirty();
}

void TableView::set_data(const char* data[10][5], usize rows, usize cols) {
    m_row_count = rows > 10 ? 10 : rows;
    m_col_count = cols > 5 ? 5 : cols;
    for (usize r = 0; r < m_row_count; r++) {
        for (usize c = 0; c < m_col_count; c++) {
            m_data[r][c] = data[r][c];
        }
    }
    set_paint_dirty();
}

RenderTableView::RenderTableView() : m_col_count(0), m_row_count(0) {
    for (int i = 0; i < 5; i++) {
        m_columns[i] = nullptr;
        for (int j = 0; j < 10; j++) {
            m_data[j][i] = nullptr;
        }
    }
}

void RenderTableView::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    // Draw background
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF1E1E1E);
    renderer->draw_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF4A4A4B);

    u32 cell_w = m_col_count > 0 ? (m_rect.w / m_col_count) : m_rect.w;
    u32 row_h = 24;

    // Draw headers
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, row_h, 0xFF2D2D2D);
    for (usize c = 0; c < m_col_count; c++) {
        if (m_columns[c]) {
            renderer->draw_text(m_columns[c], m_rect.x + c * cell_w + 4, m_rect.y + 4, 0xFFFFFFFF);
        }
        renderer->draw_line(m_rect.x + c * cell_w, m_rect.y, m_rect.x + c * cell_w, m_rect.y + m_rect.h, 0xFF4A4A4B);
    }
    renderer->draw_line(m_rect.x, m_rect.y + row_h, m_rect.x + m_rect.w, m_rect.y + row_h, 0xFF4A4A4B);

    // Draw data cells
    for (usize r = 0; r < m_row_count; r++) {
        u32 ry = m_rect.y + row_h + r * row_h;
        if (ry + row_h > (u32)(m_rect.y + m_rect.h)) break;

        for (usize c = 0; c < m_col_count; c++) {
            if (m_data[r][c]) {
                renderer->draw_text(m_data[r][c], m_rect.x + c * cell_w + 4, ry + 4, 0xFFCCCCCC);
            }
        }
        renderer->draw_line(m_rect.x, ry + row_h, m_rect.x + m_rect.w, ry + row_h, 0xFF4A4A4B);
    }
}

void RenderTableView::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}

void RenderTableView::set_columns(const char** cols, usize count) {
    m_col_count = count > 5 ? 5 : count;
    for (usize i = 0; i < m_col_count; i++) {
        m_columns[i] = cols[i];
    }
}

void RenderTableView::set_data(const char* data[10][5], usize rows, usize cols) {
    m_row_count = rows > 10 ? 10 : rows;
    m_col_count = cols > 5 ? 5 : cols;
    for (usize r = 0; r < m_row_count; r++) {
        for (usize c = 0; c < m_col_count; c++) {
            m_data[r][c] = data[r][c];
        }
    }
}

} // namespace acos::gui::widgets
