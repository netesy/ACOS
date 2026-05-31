#include "window_widget.h"
#include "theme.h"
#include <kernel/memory/heap.h>

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_child_count(0), m_window_handle(0) {
    m_rect = {x, y, w, h};
}

WindowWidget::~WindowWidget() {}

void WindowWidget::add_child(Widget* child) {
    if (m_child_count < 32) {
        m_children[m_child_count++] = child;
        child->set_parent(this);
    }
}

void WindowWidget::draw(u32* buffer, u32 pitch) {
    // Draw background
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = g_current_theme.background;
        }
    }

    // Draw children
    for (usize i = 0; i < m_child_count; i++) {
        if (m_children[i]->is_visible()) {
            m_children[i]->draw(buffer, pitch);
        }
    }
}

void WindowWidget::show() {
    // In a real implementation, this would send an IPC message to the Display Server
    // to create a native window and map its buffer.
}

} // namespace acos::gui
