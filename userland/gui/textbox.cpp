#include "textbox.h"
#include "theme.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::gui {

TextBox::TextBox() : m_cursor(0) {
    m_rect.w = 150;
    m_rect.h = 25;
    m_buffer[0] = '\0';
}

void TextBox::draw(u32* buffer, u32 pitch) {
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = 0xFFFFFFFF; // White background
        }
    }
}

void TextBox::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Keyboard) {
        // Handle typing
    }
}

void TextBox::set_text(const char* text) {
    (void)text;
}

} // namespace acos::gui
