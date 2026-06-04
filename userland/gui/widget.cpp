#include "widget.h"
#include "context.h"

namespace acos::ui {

Widget::Widget() : m_parent(Ref<Widget>::null()), m_layout_node(Ref<LayoutNode>::null()),
    m_render_object(Ref<RenderObject>::null()), m_dirty(true) {
    m_style = {0, 0xFFFFFFFF, -1, -1, -1, -1, false};
}

void Widget::add_child(UIContext* ctx, Ref<Widget> child) {
    if (child.is_null()) return;
    m_children.add(ctx->region(), child);
    mark_dirty();
}

Widget& Widget::background(u32 color) {
    m_style.background_color = color;
    m_style.has_background = true;
    mark_dirty();
    return *this;
}

} // namespace acos::ui
