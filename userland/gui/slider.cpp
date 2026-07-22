#include <acos/process.h>
#include <acos/runtime.h>
#include "slider.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Slider::Slider() : m_value(0), m_min(0), m_max(100) {
    m_rect = {0, 0, 150, 24};
}

Slider::~Slider() {}

Ref<RenderObject> Slider::create_render_object() {
    return UIContext::get().region().alloc<RenderSlider>();
}

void Slider::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rs = static_cast<RenderSlider*>(render_object.operator->());
    if (rs) {
        rs->set_value(m_value);
        rs->set_range(m_min, m_max);
    }
}

void Slider::set_value(float value) {
    m_value = value;
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
    set_paint_dirty();
}

void Slider::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_paint_dirty();
}

void Slider::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        ::acos::i32 mx = event.mouse_x;
        bool pressed = (raw.value & 0x01) != 0;

        // Event dispatcher already performed hit testing, so we only receive events when over this widget
        if (pressed) {
            m_state = WidgetState::Pressed;
            float pct = (float)(mx - m_rect.x) / (float)m_rect.w;
            if (pct < 0.0f) pct = 0.0f;
            if (pct > 1.0f) pct = 1.0f;
            set_value(m_min + pct * (m_max - m_min));
        } else {
            m_state = WidgetState::Hovered;
        }
        event.stop_propagation();
    }
}

} // namespace acos::gui::widgets
