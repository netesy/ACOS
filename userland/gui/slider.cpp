#include "slider.h"
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
    (void)event;
}

} // namespace acos::gui::widgets
