#include "panel.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Panel::Panel() : m_bg_color(0), m_is_glass(false) {
    m_rect = {0, 0, 100, 100};
}

Panel::~Panel() {}

Ref<RenderObject> Panel::create_render_object() {
    return UIContext::get().region().alloc<RenderPanel>();
}

void Panel::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rp = static_cast<RenderPanel*>(render_object.operator->());
    if (rp) {
        rp->set_glass(m_is_glass);
    }
}

} // namespace acos::gui::widgets
