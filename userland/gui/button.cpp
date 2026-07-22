#include <acos/process.h>
#include <acos/runtime.h>
#include "button.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "core/event_dispatcher.h"

namespace acos::gui::widgets {

Button::Button(const char* label) : m_label(label), m_mouse_over(false) {
    i32 w = 100;
    if (label) {
        i32 label_w = 0;
        while (label[label_w]) label_w++;
        w = label_w * 8 + 20;
    }
    m_rect = {0, 0, w, 32};
}

Button::~Button() {}

void Button::update(::acos::u64 delta_ms) {
    Widget::update(delta_ms);
}

Ref<RenderObject> Button::create_render_object() {
    return UIContext::get().region().alloc<RenderButton>();
}

void Button::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rb = static_cast<RenderButton*>(render_object.operator->());
    if (rb) {
        rb->set_label(m_label);
        rb->set_hovered(m_mouse_over);
        rb->set_pressed(m_state == WidgetState::Pressed);
    }
}

void Button::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        bool pressed = (raw.value & 0x01) != 0;

        // Event dispatcher already performed hit testing, so we only receive events when over this widget
        m_mouse_over = true;
        if (pressed) {
            m_state = WidgetState::Pressed;
        } else {
            if (m_state == WidgetState::Pressed && m_on_click) {
                m_on_click(m_on_click_arg);
            }
            m_state = WidgetState::Hovered;
        }
        set_paint_dirty();
    }
}

} // namespace acos::gui::widgets
