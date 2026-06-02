#include "label.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

Label::Label(const char* text) 
    : m_text(text), m_text_color(g_current_theme.text), 
      m_alignment(TextAlignment::Left), m_font_size(16) {
    m_rect.w = 200;
    m_rect.h = 24;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
}

Label::~Label() {}

void Label::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible) || !m_text) return;
    
    acos::graphics::Font::Alignment align = acos::graphics::Font::Alignment::Left;
    u32 tx = (u32)m_rect.x;
    u32 ty = (u32)(m_rect.y + (m_rect.h / 2) - 8);

    if (m_alignment == TextAlignment::Center) {
        align = acos::graphics::Font::Alignment::Center;
        tx = (u32)(m_rect.x + m_rect.w / 2);
    } else if (m_alignment == TextAlignment::Right) {
        align = acos::graphics::Font::Alignment::Right;
        tx = (u32)(m_rect.x + m_rect.w);
    }
    
    renderer->draw_text(m_text, tx, ty, m_text_color, align);
}

} // namespace acos::gui
