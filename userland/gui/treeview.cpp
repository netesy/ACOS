#include "treeview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

TreeView::TreeView() : m_root_count(0) {
    m_rect = {0, 0, 100, 100};
}

TreeView::~TreeView() {}

Ref<RenderObject> TreeView::create_render_object() {
    return Ref<RenderObject>();
}

void TreeView::add_root_item(const char* label) {
    if (m_root_count < 16) {
        m_roots[m_root_count++] = {label, false, {nullptr}, 0};
    }
}

} // namespace acos::gui::widgets
