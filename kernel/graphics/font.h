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

class Renderer;

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

    Font() : m_valid(false), m_width(0), m_height(0), m_charsize(0), m_headersize(0), m_data(nullptr), m_data_size(0), m_is_psf2(false) {}
    Font(const u8* data, usize size);
    Font(acos::Span<const u8> data) : Font(data.data(), data.size()) {}

    bool is_valid() const { return m_valid; }
    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    u32 char_size() const { return m_charsize; }

    void measure_char(char c, u32& w, u32& h) const;
    void measure_string(const char* str, u32& w, u32& h, i32 spacing = 0) const;

    const u8* get_glyph(char c) const;

    static void set_default(Font* font);
    static Font* get_default();
    static void measure_string_default(const char* str, u32& w, u32& h, i32 spacing = 0);

private:
    static Font* s_default_font;

    bool m_valid;
    u32 m_width;
    u32 m_height;
    u32 m_charsize;
    u32 m_headersize;
    const u8* m_data;
    [[maybe_unused]] usize m_data_size;
    bool m_is_psf2;
    bool m_is_ttf;
    u8 m_rendered_data[256 * 16];
};

} // namespace acos::graphics
