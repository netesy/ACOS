#include "switch.h"
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
    (void)event;
}

} // namespace acos::gui::widgets
