#include "scrollview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ScrollView::ScrollView() : m_v_scroll(Orientation::Vertical), m_content(nullptr) {
    m_rect = {0, 0, 200, 200};
    m_v_scroll.set_parent(this);
}

ScrollView::~ScrollView() {}

void ScrollView::add_content(Widget* widget) {
    m_content = widget;
    widget->set_parent(this);
}

void ScrollView::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.border);

    m_v_scroll.set_position(m_rect.x + m_rect.w - 12, m_rect.y);
    m_v_scroll.set_size(12, m_rect.h);
    m_v_scroll.draw(renderer);

    if (m_content) {
        acos::graphics::ClipRect clip = {m_rect.x + 2, m_rect.y + 2, m_rect.w - 16, m_rect.h - 4};
        renderer->set_clip_rect(clip);

        i32 offset_y = m_v_scroll.value();
        // Just setting position is enough as draw_pixel will handle clipping
        m_content->set_position(m_rect.x + 4, m_rect.y + 4 - offset_y);
        m_content->draw(renderer);

        renderer->clear_clip_rect();
    }
}

void ScrollView::handle_event(const acos::input::InputEvent& event) {
    m_v_scroll.handle_event(event);
    if (m_content) m_content->handle_event(event);
}

} // namespace acos::gui
