#include <acos/font.h>

namespace acos::graphics {

Font::Font(const u8* data, usize size)
    : m_valid(false), m_width(0), m_height(0), m_charsize(0), m_headersize(0), m_data(data), m_data_size(size), m_is_psf2(false)
{
    if (!data || size < 4) return;

    if (data[0] == 0x36 && data[1] == 0x04) {
        m_is_psf2 = false;
        m_width = 8;
        m_height = data[3];
        m_charsize = data[3];
        m_headersize = 4;
        m_valid = true;
        return;
    }

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

} // namespace acos::graphics
