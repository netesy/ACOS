#include "label.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

// Helper function for string length
static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

Label::Label(const char* text) 
    : m_text(text), m_text_color(g_current_theme.text), 
      m_alignment(TextAlignment::Left), m_font_size(8) {
    m_rect.w = 200;
    m_rect.h = 20;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
}

Label::~Label() {}

void Label::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    if (!m_text) return;
    
    i32 text_x = m_rect.x;
    usize text_len = strlen_impl(m_text);
    
    // Calculate alignment
    switch (m_alignment) {
        case TextAlignment::Center:
            text_x = m_rect.x + (m_rect.w / 2) - (i32)(text_len * 4);
            break;
        case TextAlignment::Right:
            text_x = m_rect.x + m_rect.w - (i32)(text_len * 8);
            break;
        case TextAlignment::Left:
        default:
            break;
    }
    
    renderer->draw_text(m_text, (u32)text_x, (u32)m_rect.y, m_text_color);
}

} // namespace acos::gui
