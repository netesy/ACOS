#include "scrollview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ScrollView::ScrollView() : m_v_scroll(Orientation::Vertical), m_content(nullptr) {
    m_rect = {0, 0, 200, 200};
    m_v_scroll.set_parent(this);
}

ScrollView::~ScrollView() {}

void ScrollView::add_content(Widget* widget) {
    m_content = widget;
    widget->set_parent(this);
}



Ref<RenderObject> Scrollview::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ScrollView::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
