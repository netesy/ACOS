#include <acos/font_manager.h>
#include "spleen_font_data.h"
#include "inter_data.h"

namespace acos::graphics {

Font FontManager::m_console_font;
Font FontManager::m_ui_font;

bool FontManager::initialize() {
    m_console_font = Font(acos::Span<const u8>(fonts_spleen_8x16_psf, fonts_spleen_8x16_psf_len));
    m_ui_font = Font(acos::Span<const u8>(inter_ttf, inter_ttf_len));
    if (!m_ui_font.is_valid()) {
        m_ui_font = m_console_font;
    }
    return m_console_font.is_valid();
}

Font* FontManager::get_font(FontID id) {
    if (id == FontID::UIDefault) {
        return &m_ui_font;
    }
    return &m_console_font;
}

} // namespace acos::graphics
