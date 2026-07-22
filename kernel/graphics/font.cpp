#include <kernel/graphics/font.h>
#include <kernel/graphics/graphics_manager.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>

// Override math / memory functions for freestanding stb_truetype
extern "C" double floor(double x);
extern "C" double ceil(double x);
extern "C" double sqrt(double x);
extern "C" double fabs(double x);

#define STBTT_malloc(x,u)  ((void)(u), acos::memory::kmalloc(x))
#define STBTT_free(x,u)    ((void)(u), acos::memory::kfree(x))
#define STBTT_assert(x)    ((void)0)

inline int stbtt_ifloor(double x) {
    int i = (int)x;
    return (x < i) ? i - 1 : i;
}
inline int stbtt_iceil(double x) {
    int i = (int)x;
    return (x > i) ? i + 1 : i;
}
inline double stbtt_fabs(double x) {
    return x < 0 ? -x : x;
}
inline double stbtt_sqrt(double x) {
    if (x <= 0) return 0;
    double z = 1.0;
    for (int i = 0; i < 6; i++) {
        z -= (z * z - x) / (2.0 * z);
    }
    return z;
}
inline double stbtt_pow(double x, double y) {
    (void)y;
    if (x == 0.0) return 0.0;
    bool neg = x < 0;
    if (neg) x = -x;
    double z = x > 1.0 ? x : 1.0;
    for (int i = 0; i < 10; i++) {
        z = (2.0 * z + x / (z * z)) / 3.0;
    }
    return neg ? -z : z;
}
inline double stbtt_cos(double x) {
    double pi = 3.14159265358979323846;
    double twopi = 2.0 * pi;
    x = x - (int)(x / twopi) * twopi;
    if (x < -pi) x += twopi;
    if (x > pi) x -= twopi;
    double xx = x * x;
    return 1.0 - xx/2.0 + (xx*xx)/24.0 - (xx*xx*xx)/720.0 + (xx*xx*xx*xx)/40320.0;
}
inline double stbtt_acos(double x) {
    if (x < -1.0) x = -1.0;
    if (x > 1.0) x = 1.0;
    double pi = 3.14159265358979323846;
    return pi/2.0 - x - (x*x*x)/6.0 - (3.0*x*x*x*x*x)/40.0;
}
inline double stbtt_fmod(double x, double y) {
    if (y == 0.0) return 0.0;
    double q = x / y;
    return x - (int)q * y;
}

#define STBTT_ifloor(x)    stbtt_ifloor(x)
#define STBTT_iceil(x)     stbtt_iceil(x)
#define STBTT_sqrt(x)      stbtt_sqrt(x)
#define STBTT_pow(x,y)     stbtt_pow(x,y)
#define STBTT_fmod(x,y)    stbtt_fmod(x,y)
#define STBTT_cos(x)       stbtt_cos(x)
#define STBTT_acos(x)      stbtt_acos(x)
#define STBTT_fabs(x)      stbtt_fabs(x)

#define STBTT_memcpy       memcpy
#define STBTT_memset       memset
#define STBTT_strlen(x)    strlen(x)

#define STB_TRUETYPE_IMPLEMENTATION
#include <libs/stb_truetype.h>

namespace acos::graphics {

Font* Font::s_default_font = nullptr;

Font::Font(const u8* data, usize size)
    : m_valid(false), m_width(0), m_height(0), m_charsize(0), m_headersize(0), m_data(data), m_data_size(size), m_is_psf2(false), m_is_ttf(false), m_glyph_alpha(nullptr)
{
    for (int i = 0; i < 256; i++) {
        m_glyph_widths[i] = 8;
    }
    if (!data || size < 4) return;

    // Check PSF1 magic: 0x36 0x04
    if (data[0] == 0x36 && data[1] == 0x04) {
        m_is_psf2 = false;
        m_width = 8;
        m_height = data[3];
        m_charsize = data[3];
        m_headersize = 4;
        m_valid = true;
        for (int i = 0; i < 256; i++) {
            m_glyph_widths[i] = m_width;
        }
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
        for (int i = 0; i < 256; i++) {
            m_glyph_widths[i] = m_width;
        }
        return;
    }

    // Check TTF magic: 0x00 0x01 0x00 0x00 or 'OTTO'
    if ((data[0] == 0x00 && data[1] == 0x01 && data[2] == 0x00 && data[3] == 0x00) ||
        (data[0] == 'O' && data[1] == 'T' && data[2] == 'T' && data[3] == 'O')) {
        m_is_ttf = true;
        m_width = 12; // cell width 12 to support proportional widths up to 12px
        m_height = 16;
        m_charsize = 16;
        m_headersize = 0;

        for (int i = 0; i < 256; i++) {
            m_glyph_widths[i] = 8; // fallback default
        }

        m_glyph_alpha = static_cast<u8*>(acos::memory::kmalloc(256 * 12 * 16));
        if (m_glyph_alpha) {
            for (int i = 0; i < 256 * 12 * 16; i++) {
                m_glyph_alpha[i] = 0;
            }

            stbtt_fontinfo font_info;
            if (stbtt_InitFont(&font_info, data, 0)) {
                m_valid = true;
                float scale = stbtt_ScaleForPixelHeight(&font_info, 16.0f);
                int ascent, descent, lineGap;
                stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &lineGap);
                int scaled_ascent = (int)(ascent * scale);

                for (int c = 0; c < 256; c++) {
                    int x1, y1, x2, y2;
                    stbtt_GetCodepointBitmapBox(&font_info, c, scale, scale, &x1, &y1, &x2, &y2);
                    int gw = x2 - x1;
                    int gh = y2 - y1;

                    // Parse proportional horizontal advance width
                    int advance_width, left_side_bearing;
                    stbtt_GetCodepointHMetrics(&font_info, c, &advance_width, &left_side_bearing);
                    int char_w = (int)(advance_width * scale + 0.5f);
                    if (char_w <= 0) {
                        char_w = gw > 0 ? gw + 2 : 8;
                    }
                    if (char_w > 12) char_w = 12;
                    m_glyph_widths[c] = char_w;

                    if (gw > 0 && gh > 0 && (gw * gh <= 1024)) {
                        u8 glyph_pixels[1024] = {0};
                        stbtt_MakeCodepointBitmap(&font_info, glyph_pixels, gw, gh, gw, scale, scale, c);

                        int baseline = scaled_ascent;
                        int start_y = baseline + y1;

                        // Left-align with exact typographical Left Side Bearing alignment,
                        // keeping the glyph neatly aligned inside its proportional cell width.
                        int start_x = (int)(left_side_bearing * scale + 0.5f);
                        if (start_x < 0) start_x = 0;
                        if (start_x + gw > 12) start_x = 12 - gw;
                        if (start_x < 0) start_x = 0;

                        u8* cell = m_glyph_alpha + (c * 12 * 16);
                        for (int gy = 0; gy < gh; gy++) {
                            int py = start_y + gy;
                            if (py < 0 || py >= 16) continue;
                            for (int gx = 0; gx < gw; gx++) {
                                int px = start_x + gx;
                                if (px < 0 || px >= 12) continue;
                                // Keep the raw stb_truetype coverage value (0-255)
                                // instead of thresholding it to on/off. This is
                                // what makes antialiased edges possible.
                                cell[py * 12 + px] = glyph_pixels[gy * gw + gx];
                            }
                        }
                    }
                }
            }
        }
    }
}

const u8* Font::get_glyph(char c) const {
    if (!m_valid) return nullptr;
    if (m_is_ttf) {
        // Legacy hard-edged path: not used for antialiased drawing, kept
        // only in case a caller still wants a boolean glyph shape.
        return nullptr;
    }
    if (!m_data) return nullptr;
    u32 index = static_cast<u8>(c);
    return m_data + m_headersize + (index * m_charsize);
}

const u8* Font::get_glyph_alpha(char c) const {
    if (!m_valid || !m_is_ttf || !m_glyph_alpha) return nullptr;
    u32 index = static_cast<u8>(c);
    return m_glyph_alpha + (index * m_width * m_height);
}

u32 Font::get_char_width(char c) const {
    if (!m_valid) return 8;
    return m_glyph_widths[static_cast<u8>(c)];
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
