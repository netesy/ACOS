#include "stackwidget.h"

namespace acos::gui {

StackWidget::StackWidget() : m_count(0), m_current_index(0) {}

void StackWidget::add_widget(Widget* widget) {
    if (m_count < 16) {
        m_pages[m_count++] = widget;
        widget->set_parent(this);
        widget->set_visible(m_count - 1 == m_current_index);
    }
}

void StackWidget::set_current_index(u32 index) {
    if (index < m_count) {
        m_pages[m_current_index]->set_visible(false);
        m_current_index = index;
        m_pages[m_current_index]->set_visible(true);
    }
}

void StackWidget::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;
    if (m_current_index < m_count) {
        m_pages[m_current_index]->set_rect(m_rect);
        m_pages[m_current_index]->draw(renderer);
    }
}

void StackWidget::handle_event(const acos::input::InputEvent& event) {
    if (m_current_index < m_count) {
        m_pages[m_current_index]->handle_event(event);
    }
}

} // namespace acos::gui
