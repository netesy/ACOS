#include <acos/process.h>
#include <acos/runtime.h>
#include "checkbox.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

CheckBox::CheckBox(const char* label) : m_label(label), m_checked(false) {
    m_rect = {0, 0, 120, 24};
}

CheckBox::~CheckBox() {}

Ref<RenderObject> CheckBox::create_render_object() {
    return UIContext::get().region().alloc<RenderCheckBox>();
}

void CheckBox::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rc = static_cast<RenderCheckBox*>(render_object.operator->());
    if (rc) {
        rc->set_label(m_label);
        rc->set_checked(m_checked);
    }
}

void CheckBox::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        ::acos::i32 mx = event.mouse_x;
        ::acos::i32 my = event.mouse_y;
        bool pressed = (raw.value & 0x01) != 0;

        if (m_rect.contains(mx, my)) {
            if (pressed) {
                m_state = WidgetState::Pressed;
            } else {
                if (m_state == WidgetState::Pressed) {
                    m_checked = !m_checked;
                    set_paint_dirty();
                }
                m_state = WidgetState::Hovered;
            }
            event.stop_propagation();
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

} // namespace acos::gui::widgets
