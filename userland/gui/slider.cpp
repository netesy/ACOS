#include "slider.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Slider::Slider() : m_value(0.0f), m_min(0.0f), m_max(100.0f), m_dragging(false) {
    m_rect.w = 200;
    m_rect.h = 24;
}

Slider::~Slider() {}

void Slider::set_value(float v) {
    if (v < m_min) m_value = m_min;
    else if (v > m_max) m_value = m_max;
    else m_value = v;
    set_paint_dirty();
}

void Slider::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_value(m_value);
}

Ref<RenderObject> Slider::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderSlider>();
    update_render_object(ro);
    return ro;
}

void Slider::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderSlider* rs = static_cast<RenderSlider*>(render_object.operator->());
        rs->set_value(m_value);
        rs->set_range(m_min, m_max);
    }
}

void Slider::on_event(Event& event) {
    if (!is_enabled()) return;

    if (event.raw.type == acos::input::InputType::Mouse) {
        bool pressed = (event.raw.value & 0x01) != 0;

        if (pressed && event.phase == EventPhase::Target) {
            m_dragging = true;
        } else if (!pressed) {
            m_dragging = false;
        }

        if (m_dragging) {
            float ratio = (float)(event.mouse_x - m_rect.x) / m_rect.w;
            if (ratio < 0.0f) ratio = 0.0f;
            if (ratio > 1.0f) ratio = 1.0f;
            set_value(m_min + ratio * (m_max - m_min));
            event.stop_propagation();
        }
    }
}

} // namespace acos::gui::widgets
