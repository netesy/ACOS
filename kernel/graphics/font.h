#pragma once
#include <acos/types.h>
#include <acos/span.h>

namespace acos::graphics {

struct PSF1Header {
    u16 magic;
    u8 mode;
    u8 charsize;
};

struct PSF2Header {
    u32 magic;
    u32 version;
    u32 headersize;
    u32 flags;
    u32 length;
    u32 charsize;
    u32 height;
    u32 width;
};

class Font {
public:
    enum class Style {
        Regular = 0,
        Bold = 1,
        Italic = 2
    };

    enum class Alignment {
        Left,
        Center,
        Right
    };

    Font() = default;
    Font(acos::Span<const u8> data);

    bool is_valid() const { return m_valid; }
    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    u32 char_size() const { return m_charsize; }

    void measure_char(char c, u32& w, u32& h) const;
    void measure_string(const char* str, u32& w, u32& h, i32 spacing = 0) const;

    void draw_char(char c, u32 x, u32 y, u32 color, Style style = Style::Regular) const;
    void draw_string(const char* str, u32 x, u32 y, u32 color, Alignment align = Alignment::Left, Style style = Style::Regular, i32 spacing = 0) const;

    static void set_default(Font* font);
    static Font* get_default();
    static void measure_string_default(const char* str, u32& w, u32& h, i32 spacing = 0);
    static void draw_char_default(char c, u32 x, u32 y, u32 color, Style style = Style::Regular);
    static void draw_string_default(const char* str, u32 x, u32 y, u32 color, Alignment align = Alignment::Left, Style style = Style::Regular, i32 spacing = 0);

private:
    bool m_valid = false;
    u32 m_width = 0;
    u32 m_height = 0;
    u32 m_charsize = 0;
    u32 m_headersize = 0;
    acos::Span<const u8> m_data;
    bool m_is_psf2 = false;

    const u8* get_glyph(char c) const;
};

} // namespace acos::graphics
