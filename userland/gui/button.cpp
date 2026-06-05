#include "button.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "core/event_dispatcher.h"

namespace acos::gui::widgets {

Button::Button(const char* label) : m_label(label), m_mouse_over(false), m_press_time(0) {
    m_rect = {0, 0, 100, 32};
}

Button::~Button() {}

void Button::update(u64 delta_ms) {
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
    if (raw.type == acos::input::InputType::Mouse) {
        i32 mx = (raw.code >> 16) & 0xFFFF;
        i32 my = raw.code & 0xFFFF;
        bool pressed = (raw.value & 0x01) != 0;

        if (m_rect.contains(mx, my)) {
            m_mouse_over = true;
            if (pressed) {
                m_state = WidgetState::Pressed;
            } else {
                if (m_state == WidgetState::Pressed && m_on_click) {
                    m_on_click(nullptr);
                }
                m_state = WidgetState::Hovered;
            }
        } else {
            m_mouse_over = false;
            m_state = WidgetState::Normal;
        }
        set_paint_dirty();
    }
}

} // namespace acos::gui::widgets
