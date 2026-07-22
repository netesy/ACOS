#include <acos/process.h>
#include <acos/runtime.h>
#include "switch.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Switch::Switch(const char* label) : m_label(label), m_on(false) {
    m_rect = {0, 0, 100, 24};
}

Switch::~Switch() {}

Ref<RenderObject> Switch::create_render_object() {
    return UIContext::get().region().alloc<RenderSwitch>();
}

void Switch::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rs = static_cast<RenderSwitch*>(render_object.operator->());
    if (rs) {
        rs->set_label(m_label);
        rs->set_on(m_on);
    }
}

void Switch::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        bool pressed = (raw.value & 0x01) != 0;

        // Event dispatcher already performed hit testing, so we only receive events when over this widget
        if (pressed) {
            m_state = WidgetState::Pressed;
        } else {
            if (m_state == WidgetState::Pressed) {
                m_on = !m_on;
                set_paint_dirty();
            }
            m_state = WidgetState::Hovered;
        }
        event.stop_propagation();
    }
}

} // namespace acos::gui::widgets
