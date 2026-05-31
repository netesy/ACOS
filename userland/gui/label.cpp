#include "label.h"
#include "theme.h"

namespace acos::gui {

Label::Label(const char* text) : m_text(text) {
    m_rect.w = 100;
    m_rect.h = 20;
}

void Label::draw(u32* buffer, u32 pitch) {
    (void)buffer; (void)pitch;
    // Draw text using Font engine
}

} // namespace acos::gui
