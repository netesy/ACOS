#include "label.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::gui {

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
    
    u32 text_x = m_rect.x;
    u32 text_len = acos::runtime::strlen(m_text);
    
    // Calculate alignment
    switch (m_alignment) {
        case TextAlignment::Center:
            text_x = m_rect.x + (m_rect.w / 2) - (text_len * 4);
            break;
        case TextAlignment::Right:
            text_x = m_rect.x + m_rect.w - (text_len * 8);
            break;
        case TextAlignment::Left:
        default:
            break;
    }
    
    renderer->draw_text(m_text, text_x, m_rect.y, m_text_color);
}

} // namespace acos::gui
