#include <acos/font_manager.h>
#include "spleen_font_data.h"

namespace acos::graphics {

Font FontManager::m_console_font;

bool FontManager::initialize() {
    m_console_font = Font(acos::Span<const u8>(fonts_spleen_8x16_psf, fonts_spleen_8x16_psf_len));
    return m_console_font.is_valid();
}

Font* FontManager::get_font(FontID id [[maybe_unused]]) {
    return &m_console_font;
}

} // namespace acos::graphics
