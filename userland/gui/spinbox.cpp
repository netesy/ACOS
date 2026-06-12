#include <acos/process.h>
#include <acos/runtime.h>
#include "spinbox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

SpinBox::SpinBox(::acos::i32 min, ::acos::i32 max) : m_value(min), m_min(min), m_max(max), m_up_hovered(false), m_down_hovered(false) {
    m_rect = {0, 0, 100, 32};
}

SpinBox::~SpinBox() {}

Ref<RenderObject> SpinBox::create_render_object() {
    return Ref<RenderObject>();
}

void SpinBox::set_value(::acos::i32 value) {
    if (value >= m_min && value <= m_max) {
        m_value = value;
    }
}

} // namespace acos::gui::widgets
