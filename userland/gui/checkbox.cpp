#include "checkbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

CheckBox::CheckBox(const char* label) : m_label(label), m_checked(false) {
    m_rect.w = 120;
    m_rect.h = 24;
}

CheckBox::~CheckBox() {}

Ref<RenderObject> CheckBox::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderCheckBox>();
    update_render_object(ro);
    return ro;
}

void CheckBox::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderCheckBox* rcb = static_cast<RenderCheckBox*>(render_object.operator->());
        rcb->set_label(m_label);
        rcb->set_checked(m_checked);
    }
}

void CheckBox::on_event(Event& event) {
    if (!is_enabled()) return;

    if (event.raw.type == acos::input::InputType::Mouse) {
        bool pressed = (event.raw.value & 0x01) != 0;

        if (event.phase == EventPhase::Target && pressed) {
            set_checked(!m_checked);
            event.stop_propagation();
        }
    }
}

} // namespace acos::gui
