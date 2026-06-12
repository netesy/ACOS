#include <acos/process.h>
#include <acos/runtime.h>
#include "scrollbar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ScrollBar::ScrollBar(Orientation orientation) : m_orientation(orientation), m_value(0), m_min(0), m_max(100), m_page_size(10), m_dragging(false), m_drag_start(0) {
    m_rect = {0, 0, 16, 100};
}

ScrollBar::~ScrollBar() {}

Ref<RenderObject> ScrollBar::create_render_object() {
    return Ref<RenderObject>();
}

void ScrollBar::set_value(::acos::i32 value) {
    m_value = value;
}

void ScrollBar::set_range(::acos::i32 min, ::acos::i32 max, ::acos::i32 page_size) {
    m_min = min;
    m_max = max;
    m_page_size = page_size;
}

} // namespace acos::gui::widgets
