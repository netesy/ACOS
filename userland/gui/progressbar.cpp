#include "progressbar.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

ProgressBar::ProgressBar() : m_value(0), m_min(0), m_max(100) {
    m_rect = {0, 0, 200, 16};
}

ProgressBar::~ProgressBar() {}

Ref<RenderObject> ProgressBar::create_render_object() {
    return UIContext::get().region().alloc<RenderProgressBar>();
}

void ProgressBar::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rp = static_cast<RenderProgressBar*>(render_object.operator->());
    if (rp) {
        rp->set_value(m_value);
        rp->set_range(m_min, m_max);
    }
}

void ProgressBar::set_value(float value) {
    m_value = value;
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
    set_paint_dirty();
}

void ProgressBar::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_paint_dirty();
}

} // namespace acos::gui::widgets
