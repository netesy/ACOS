#include "treeview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

TreeView::TreeView() {
    m_rect = {0, 0, 100, 100};
}

TreeView::~TreeView() {}

Ref<RenderObject> TreeView::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
