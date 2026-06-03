#include <kernel/graphics/font_manager.h>
#include "font_data.h"
#include "jetbrains_mono_data.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::graphics {

// Font instances - static allocation
Font FontManager::m_console_font;
Font FontManager::m_ui_font;
Font FontManager::m_mono_font;

// Static builtin fonts
static Font g_builtin_fonts[3];
static bool g_fonts_loaded = false;

bool FontManager::initialize() {
    // Load console font (Spleen 8x16 PSF1 from builtin data)
    g_builtin_fonts[0] = get_builtin_font();
    
    if (g_builtin_fonts[0].is_valid()) {
        Font::set_default(&g_builtin_fonts[0]);
        m_console_font = g_builtin_fonts[0];
    }
    
    // Load monospace font (JetBrains Mono TTF from embedded binary)
    // TTF rendering requires stb_truetype or similar - for now store reference
    g_builtin_fonts[1] = Font(acos::Span<const u8>(jetbrains_mono_ttf, jetbrains_mono_ttf_len));
    if (g_builtin_fonts[1].is_valid()) {
        m_mono_font = g_builtin_fonts[1];
    }
    
    // UI font (Inter TTF) - fallback to mono for now
    m_ui_font = m_mono_font;
    
    g_fonts_loaded = true;
    return m_console_font.is_valid();
}

Font* FontManager::get_font(FontID id) {
    if (!g_fonts_loaded) {
        return nullptr;
    }
    
    switch (id) {
        case FontID::ConsolePrimary:
        case FontID::ConsoleSecondary:
            return m_console_font.is_valid() ? &m_console_font : nullptr;
        case FontID::UIDefault:
            return m_ui_font.is_valid() ? &m_ui_font : &m_console_font;
        case FontID::UIMonospace:
            return m_mono_font.is_valid() ? &m_mono_font : &m_console_font;
        default:
            return &m_console_font;
    }
}

acos::Span<const u8> FontManager::load_font_data([[maybe_unused]] FontID id) {
    // This function will be called by VFS/filesystem when fonts are available
    // For now, it's a placeholder
    return {};
}

} // namespace acos::graphics
