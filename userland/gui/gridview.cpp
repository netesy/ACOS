#include "gridview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

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



Ref<RenderObject> GridView::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> GridView::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
