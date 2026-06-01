#include "window_widget.h"
#include "theme.h"
#include <kernel/memory/heap.h>
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_child_count(0), m_window_handle(0) {
    m_rect = {x, y, w, h};
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
    m_state = WidgetState::Normal;
}

WindowWidget::~WindowWidget() {}

void WindowWidget::add_child(Widget* child) {
    if (m_child_count < 32) {
        m_children[m_child_count++] = child;
        child->set_parent(this);
    }
}

void WindowWidget::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible) || !renderer) return;

    renderer->fill_rect(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w), static_cast<u32>(m_rect.h),
                        g_current_theme.background);
    renderer->fill_rect(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w), 30, g_current_theme.accent);
    renderer->draw_border(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                          static_cast<u32>(m_rect.w), static_cast<u32>(m_rect.h),
                          g_current_theme.border, 1);
    renderer->draw_text(m_title, static_cast<u32>(m_rect.x + 8),
                        static_cast<u32>(m_rect.y + 10), g_current_theme.foreground);

    for (usize i = 0; i < m_child_count; ++i) {
        if (m_children[i] && m_children[i]->is_visible()) {
            m_children[i]->draw(renderer);
        }
    }
}

void WindowWidget::draw_to_buffer(u32* buffer [[maybe_unused]], u32 pitch [[maybe_unused]]) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // Draw window background
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            if (y >= 0 && y < 1080 && x >= 0 && x < 1920 && buffer) {
                buffer[y * pitch + x] = g_current_theme.background;
            }
        }
    }
    
    // Draw window title bar
    u32 title_bar_color = g_current_theme.accent;
    for (i32 y = m_rect.y; y < m_rect.y + 30; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            if (y >= 0 && y < 1080 && x >= 0 && x < 1920 && buffer) {
                buffer[y * pitch + x] = title_bar_color;
            }
        }
    }
    
    // Draw window border
    u32 border_color = g_current_theme.border;
    // Top border
    for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
        if (x >= 0 && x < 1920 && buffer) {
            buffer[m_rect.y * pitch + x] = border_color;
        }
    }
    // Bottom border
    for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
        if (x >= 0 && x < 1920 && buffer) {
            buffer[(m_rect.y + m_rect.h - 1) * pitch + x] = border_color;
        }
    }
    // Left border
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        if (y >= 0 && y < 1080 && buffer) {
            buffer[y * pitch + m_rect.x] = border_color;
        }
    }
    // Right border
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        if (y >= 0 && y < 1080 && buffer) {
            buffer[y * pitch + (m_rect.x + m_rect.w - 1)] = border_color;
        }
    }
}

void WindowWidget::show() {
    // Mark window as visible
    m_flags |= (u32)WidgetFlags::Visible;
    
}

} // namespace acos::gui
