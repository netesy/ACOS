#pragma once
#include <acos/types.h>
#include <acos/span.h>
#include <kernel/graphics/font.h>

namespace acos::graphics {

class FontManager {
public:
    enum class FontID {
        ConsolePrimary,      // Spleen 8x16 - kernel console
        ConsoleSecondary,    // Fallback console font
        UIDefault,           // Inter - for GUI (TrueType)
        UIMonospace,         // JetBrains Mono - for text editors, code (TrueType)
    };

    static bool initialize();
    static Font* get_font(FontID id);
    static Font* get_console_font() { return get_font(FontID::ConsolePrimary); }
    static Font* get_ui_font() { return get_font(FontID::UIDefault); }

private:
    static Font m_console_font;
    static Font m_ui_font;
    static Font m_mono_font;
    
    static acos::Span<const u8> load_font_data(FontID id);
};

} // namespace acos::graphics
