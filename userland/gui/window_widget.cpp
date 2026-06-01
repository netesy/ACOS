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

void WindowWidget::draw(u32* buffer, u32 pitch) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // Draw window background
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            if (y >= 0 && y < 1080 && x >= 0 && x < 1920) {
                buffer[y * pitch + x] = g_current_theme.background;
            }
        }
    }
    
    // Draw window title bar
    u32 title_bar_color = g_current_theme.accent;
    for (i32 y = m_rect.y; y < m_rect.y + 30; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            if (y >= 0 && y < 1080 && x >= 0 && x < 1920) {
                buffer[y * pitch + x] = title_bar_color;
            }
        }
    }
    
    // Draw window border
    u32 border_color = g_current_theme.border;
    // Top border
    for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
        if (x >= 0 && x < 1920) {
            buffer[m_rect.y * pitch + x] = border_color;
        }
    }
    // Bottom border
    for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
        if (x >= 0 && x < 1920) {
            buffer[(m_rect.y + m_rect.h - 1) * pitch + x] = border_color;
        }
    }
    // Left border
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        if (y >= 0 && y < 1080) {
            buffer[y * pitch + m_rect.x] = border_color;
        }
    }
    // Right border
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        if (y >= 0 && y < 1080) {
            buffer[y * pitch + (m_rect.x + m_rect.w - 1)] = border_color;
        }
    }
    
    // Draw title text
    if (m_title) {
        // Draw title at top-left of title bar
        acos::graphics::Renderer renderer(buffer, pitch, 1920, 1080);
        renderer.draw_text(m_title, m_rect.x + 5, m_rect.y + 8, 0xFFFFFFFF);
    }
    
    // Draw children
    for (usize i = 0; i < m_child_count; i++) {
        if (m_children[i] && m_children[i]->is_visible()) {
            m_children[i]->draw(buffer, pitch);
        }
    }
}

void WindowWidget::show() {
    // Mark window as visible
    m_flags |= (u32)WidgetFlags::Visible;
    
    // In a full system, this would:
    // 1. Connect to display server via IPC
    // 2. Request surface creation with dimensions
    // 3. Map the surface buffer into our address space
    // 4. Store the surface handle for future operations
    // 5. Register window with input router
    
    // For now, we just mark it visible and let the desktop shell render it
}
