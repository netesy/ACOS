#pragma once
#include <acos/font.h>

namespace acos::graphics {

class FontManager {
public:
    enum class FontID {
        ConsolePrimary,
        ConsoleSecondary,
        UIDefault,
        UIMonospace,
    };

    static bool initialize();
    static Font* get_font(FontID id);
    static Font* get_console_font() { return get_font(FontID::ConsolePrimary); }
    static Font* get_ui_font() { return get_font(FontID::UIDefault); }

private:
    static Font m_console_font;
    static Font m_ui_font;
    static Font m_mono_font;
};

} // namespace acos::graphics
