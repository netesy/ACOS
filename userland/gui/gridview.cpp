#include "gridview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

GridView::GridView() {
    m_rect = {0, 0, 100, 100};
}

GridView::~GridView() {}

Ref<RenderObject> GridView::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
