#include <acos/process.h>
#include <acos/runtime.h>
#include "radiobutton.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

RadioButton::RadioButton(const char* label) : m_label(label), m_selected(false), m_group(nullptr) {
    m_rect = {0, 0, 120, 24};
}

RadioButton::~RadioButton() {}

Ref<RenderObject> RadioButton::create_render_object() {
    return UIContext::get().region().alloc<RenderRadioButton>();
}

void RadioButton::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rr = static_cast<RenderRadioButton*>(render_object.operator->());
    if (rr) {
        rr->set_label(m_label);
        rr->set_selected(m_selected);
    }
}

void RadioButton::set_selected(bool selected) {
    m_selected = selected;
    set_paint_dirty();
}

void RadioButton::on_event(Event& event) {
    (void)event;
}

RadioButtonGroup::RadioButtonGroup() {}
void RadioButtonGroup::add_button(Ref<RadioButton> button) {
    if (button) {
        m_buttons.push_back(button);
        button->set_group(this);
    }
}
void RadioButtonGroup::select(Ref<RadioButton> selected_button) {
    for (auto& btn : m_buttons) {
        if (btn) btn->set_selected(btn == selected_button);
    }
}

} // namespace acos::gui::widgets
