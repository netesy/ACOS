#include "switch.h"
#include "theme.h"
#include "core/event_dispatcher.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Switch::Switch(const char* label) : m_label(label), m_on(false) {
    m_rect.w = 120;
    m_rect.h = 24;
}

Switch::~Switch() {}

Ref<RenderObject> Switch::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderSwitch>();
    update_render_object(ro);
    return ro;
}

void Switch::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderSwitch* rs = static_cast<RenderSwitch*>(render_object.operator->());
        rs->set_label(m_label);
        rs->set_on(m_on);
    }
}

void Switch::on_event(Event& event) {
    if (!is_enabled()) return;

    if (event.raw.type == acos::input::InputType::Mouse) {
        bool pressed = (event.raw.value & 0x01) != 0;

        if (pressed && event.phase == EventPhase::Target) {
            set_on(!m_on);
            event.stop_propagation();
        }
    }
}

} // namespace acos::gui::widgets
