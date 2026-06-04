#include "widget.h"
#include "context.h"
#include "layout_node.h"

namespace acos::ui {

Widget::Widget() : m_parent(Ref<Widget>::null()), m_layout_node(Ref<LayoutNode>::null()),
    m_render_object(Ref<RenderObject>::null()), m_dirty(true) {
}

void Widget::add_child(UIContext* ctx, Ref<Widget> child) {
    if (child.is_null()) return;
    m_children.add(ctx->region(), child);
    mark_dirty();
}

void Widget::mark_dirty() {
    m_dirty = true;
}

Widget& Widget::background(u32 color) { m_style.background_color = color; m_style.has_background = true; mark_dirty(); return *this; }
Widget& Widget::color(u32 color) { m_style.text_color = color; mark_dirty(); return *this; }
Widget& Widget::radius(i32 r) { m_style.corner_radius = r; mark_dirty(); return *this; }
Widget& Widget::padding(i32 p) { m_style.padding = p; mark_dirty(); return *this; }
Widget& Widget::flex(u32 f) { m_flex = f; mark_dirty(); return *this; }

} // namespace acos::ui
