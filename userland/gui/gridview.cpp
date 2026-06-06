#include "gridview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

GridView::GridView(::acos::u32 columns) : m_columns(columns), m_cell_count(0) {
    m_rect = {0, 0, 100, 100};
}

GridView::~GridView() {}

Ref<RenderObject> GridView::create_render_object() {
    return Ref<RenderObject>();
}

void GridView::add_cell(const char* text) {
    if (m_cell_count < 256) {
        m_cells[m_cell_count++] = text;
    }
}

void GridView::set_header(::acos::u32 index, const char* title) {
    if (index < 8) {
        m_headers[index] = title;
    }
}

} // namespace acos::gui::widgets
