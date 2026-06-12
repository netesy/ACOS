#include <acos/process.h>
#include <acos/runtime.h>
#include "checkbox.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

CheckBox::CheckBox(const char* label) : m_label(label), m_checked(false) {
    m_rect = {0, 0, 120, 24};
}

CheckBox::~CheckBox() {}

Ref<RenderObject> CheckBox::create_render_object() {
    return UIContext::get().region().alloc<RenderCheckBox>();
}

void CheckBox::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rc = static_cast<RenderCheckBox*>(render_object.operator->());
    if (rc) {
        rc->set_label(m_label);
        rc->set_checked(m_checked);
    }
}

void CheckBox::on_event(Event& event) {
    (void)event;
}

} // namespace acos::gui::widgets
