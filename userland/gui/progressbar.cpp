#include "progressbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ProgressBar::ProgressBar() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {
    m_rect.w = 200;
    m_rect.h = 12;
    m_style.foreground_color = g_current_theme.primary;
}

ProgressBar::~ProgressBar() {}

void ProgressBar::set_value(float value) {
    if (value < m_min) m_value = m_min;
    else if (value > m_max) m_value = m_max;
    else m_value = value;
    set_paint_dirty();
}

void ProgressBar::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_value(m_value);
}

Ref<RenderObject> ProgressBar::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderProgressBar>();
    update_render_object(ro);
    return ro;
}

void ProgressBar::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderProgressBar* rpb = static_cast<RenderProgressBar*>(render_object.operator->());
        rpb->set_value(m_value);
        rpb->set_range(m_min, m_max);
    }
}

} // namespace acos::gui
