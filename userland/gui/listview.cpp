#include "listview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect.w = 200;
    m_rect.h = 150;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Focusable;
}

void ListView::draw(acos::graphics::Renderer* renderer [[maybe_unused]]) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // For now, this is a placeholder
    // Full implementation would use the renderer to draw the list
}

void ListView::draw_to_buffer(u32* buffer [[maybe_unused]], u32 pitch [[maybe_unused]]) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // Draw background
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            if (y >= 0 && y < 1080 && x >= 0 && x < 1920 && buffer) {
                buffer[y * pitch + x] = g_current_theme.widget_bg;
            }
        }
    }
    
    // Draw border
    u32 border_color = g_current_theme.border;
    for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
        if (x >= 0 && x < 1920 && buffer) {
            buffer[m_rect.y * pitch + x] = border_color;
            buffer[(m_rect.y + m_rect.h - 1) * pitch + x] = border_color;
        }
    }
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        if (y >= 0 && y < 1080 && buffer) {
            buffer[y * pitch + m_rect.x] = border_color;
            buffer[y * pitch + (m_rect.x + m_rect.w - 1)] = border_color;
        }
    }
    
    // Draw items (placeholder - would need proper renderer)
    i32 item_y = m_rect.y + 5;
    const i32 item_height = 20;
    
    for (usize i = 0; i < m_item_count; i++) {
        if (item_y + item_height > m_rect.y + m_rect.h) break;
        
        // Draw selection highlight
        if ((i32)i == m_selected_index) {
            for (i32 y = item_y; y < item_y + item_height; y++) {
                for (i32 x = m_rect.x + 2; x < m_rect.x + m_rect.w - 2; x++) {
                    if (y >= 0 && y < 1080 && x >= 0 && x < 1920 && buffer) {
                        buffer[y * pitch + x] = g_current_theme.accent;
                    }
                }
            }
        }
        
        item_y += item_height;
    }
}

void ListView::add_item(const char* item) {
    if (m_item_count < 64 && item) {
        m_items[m_item_count++] = item;
    }
}

void ListView::clear() {
    m_item_count = 0;
    m_selected_index = -1;
}

} // namespace acos::gui
