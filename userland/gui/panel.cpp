#include "panel.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Panel::Panel() : m_bg_color(g_current_theme.surface), m_is_glass(false) {
    m_rect = {0, 0, 100, 100};
    m_style.elevation = 1;
}

Panel::~Panel() {}

Ref<RenderObject> Panel::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderPanel>();
    update_render_object(ro);
    return ro;
}

void Panel::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderPanel* rp = static_cast<RenderPanel*>(render_object.operator->());
        rp->set_glass(m_is_glass);
    }
}

} // namespace acos::gui
