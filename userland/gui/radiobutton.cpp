#include "radiobutton.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

RadioButton::RadioButton(const char* label)
    : m_label(label), m_selected(false), m_group(nullptr) {
    m_rect.w = 120;
    m_rect.h = 24;
}

RadioButton::~RadioButton() {}

void RadioButton::set_selected(bool selected) {
    if (m_selected == selected) return;
    m_selected = selected;
    if (m_selected && m_group) {
        m_group->select(self().static_cast_to<RadioButton>());
    }
    set_paint_dirty();
}

Ref<RenderObject> RadioButton::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderRadioButton>();
    update_render_object(ro);
    return ro;
}

void RadioButton::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderRadioButton* rrb = static_cast<RenderRadioButton*>(render_object.operator->());
        rrb->set_label(m_label);
        rrb->set_selected(m_selected);
    }
}

void RadioButton::on_event(Event& event) {
    if (!is_enabled()) return;

    if (event.raw.type == acos::input::InputType::Mouse) {
        bool pressed = (event.raw.value & 0x01) != 0;

        if (pressed && event.phase == EventPhase::Target) {
            set_selected(true);
            event.stop_propagation();
        }
    }
}

RadioButtonGroup::RadioButtonGroup() {}

void RadioButtonGroup::add_button(Ref<RadioButton> button) {
    if (button) {
        m_buttons.push_back(button);
        button->set_group(this);
    }
}

void RadioButtonGroup::select(Ref<RadioButton> selected_button) {
    for (auto& button : m_buttons) {
        if (button && button != selected_button) {
            button->set_selected(false);
        }
    }
}

} // namespace acos::gui::widgets
