#include <kernel/graphics/font.h>
#include <kernel/graphics/graphics_manager.h>

namespace acos::graphics {

Font* Font::s_default_font = nullptr;

Font::Font(const u8* data, usize size)
    : m_valid(false), m_width(0), m_height(0), m_charsize(0), m_headersize(0), m_data(data), m_data_size(size), m_is_psf2(false)
{
    if (!data || size < 4) return;

    // Check PSF1 magic: 0x36 0x04
    if (data[0] == 0x36 && data[1] == 0x04) {
        m_is_psf2 = false;
        m_width = 8;
        m_height = data[3];
        m_charsize = data[3];
        m_headersize = 4;
        m_valid = true;
        return;
    }

    // Check PSF2 magic: 0x72 0xb5 0x4a 0x86
    if (data[0] == 0x72 && data[1] == 0xb5 && data[2] == 0x4a && data[3] == 0x86) {
        auto psf2 = reinterpret_cast<const PSF2Header*>(data);
        m_is_psf2 = true;
        m_width = psf2->width;
        m_height = psf2->height;
        m_charsize = psf2->charsize;
        m_headersize = psf2->headersize;
        m_valid = true;
    }
}

const u8* Font::get_glyph(char c) const {
    if (!m_valid || !m_data) return nullptr;
    u32 index = static_cast<u8>(c);
    return m_data + m_headersize + (index * m_charsize);
}

void Font::measure_char([[maybe_unused]] char c, u32& w, u32& h) const {
    w = m_valid ? m_width : 8;
    h = m_valid ? m_height : 10;
}

void Font::measure_string(const char* str, u32& w, u32& h, i32 spacing) const {
    if (!str) {
        w = 0; h = 0; return;
    }
    u32 char_w = m_valid ? m_width : 8;
    u32 char_h = m_valid ? m_height : 10;

    u32 max_w = 0;
    u32 cur_w = 0;
    u32 total_h = 0;
    bool has_content = false;

    for (usize i = 0; str[i]; i++) {
        has_content = true;
        if (str[i] == '\n') {
            if (cur_w > max_w) max_w = cur_w;
            cur_w = 0;
            total_h += char_h;
        } else {
            if (cur_w > 0) cur_w += spacing;
            cur_w += char_w;
        }
    }

    if (cur_w > max_w) max_w = cur_w;
    if (has_content && cur_w > 0) total_h += char_h;

    w = max_w;
    h = total_h;
}


void Font::set_default(Font* font) { s_default_font = font; }
Font* Font::get_default() { return s_default_font; }

void Font::measure_string_default(const char* str, u32& w, u32& h, i32 spacing) {
    if (s_default_font) s_default_font->measure_string(str, w, h, spacing);
    else {
        if (!str) { w = 0; h = 0; return; }
        u32 max_w = 0;
        u32 cur_w = 0;
        u32 total_h = 0;
        bool has_content = false;
        for (usize i = 0; str[i]; i++) {
            has_content = true;
            if (str[i] == '\n') {
                if (cur_w > max_w) max_w = cur_w;
                cur_w = 0;
                total_h += 10;
            } else {
                if (cur_w > 0) cur_w += spacing;
                cur_w += 8;
            }
        }
        if (cur_w > max_w) max_w = cur_w;
        if (has_content && cur_w > 0) total_h += 10;
        w = max_w;
        h = total_h;
    }
}


} // namespace acos::graphics
