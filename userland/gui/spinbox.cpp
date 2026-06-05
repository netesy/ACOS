#include "spinbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

SpinBox::SpinBox(i32 min, i32 max)
    : m_value(min), m_min(min), m_max(max), m_up_hovered(false), m_down_hovered(false) {
    m_rect.w = 80;
    m_rect.h = 28;
    m_flags |= (u32)WidgetFlags::Focusable;
}

SpinBox::~SpinBox() {}

void SpinBox::set_value(i32 v) {
    if (v < m_min) v = m_min;
    if (v > m_max) v = m_max;
    if (m_value != v) {
        m_value = v;
        on_value_changed.emit(m_value);
    }
}



Ref<RenderObject> SpinBox::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> SpinBox::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
