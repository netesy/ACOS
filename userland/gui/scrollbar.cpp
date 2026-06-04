#include "scrollbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ScrollBar::ScrollBar(Orientation orientation)
    : m_orientation(orientation), m_value(0), m_min(0), m_max(100), m_page_size(10),
      m_dragging(false), m_drag_start(0) {
    if (m_orientation == Orientation::Vertical) {
        m_rect.w = 12;
        m_rect.h = 100;
    } else {
        m_rect.w = 100;
        m_rect.h = 12;
    }
}

ScrollBar::~ScrollBar() {}

void ScrollBar::set_value(i32 v) {
    if (v < m_min) m_value = m_min;
    else if (v > m_max - m_page_size) m_value = m_max - m_page_size;
    else m_value = v;
}

void ScrollBar::set_range(i32 min, i32 max, i32 page_size) {
    m_min = min;
    m_max = max;
    m_page_size = page_size;
    set_value(m_value);
}



Ref<RenderObject> Scrollbar::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ScrollBar::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
