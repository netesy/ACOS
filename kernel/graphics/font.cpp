#include <kernel/graphics/font.h>
#include <kernel/graphics/graphics_manager.h>

namespace acos::graphics {

namespace {
Font* g_default_font = nullptr;

bool legacy_glyph_pixel(char c, int row, int col) {
    const u8 ch = static_cast<u8>(c);
    if (ch <= 0x20) return false;
    const u8 pattern = static_cast<u8>((ch >> ((row + col) & 3)) ^ (ch << ((row ^ col) & 1)));
    return row == 0 || row == 7 || col == 0 || col == 7 || ((pattern >> (col & 7)) & 1U) != 0;
}

Framebuffer* active_framebuffer() {
    DisplayDevice* display = GraphicsManager::primary_display();
    return display ? display->get_framebuffer() : nullptr;
}

}

Font::Font(acos::Span<const u8> data) : m_data(data) {
    if (data.size() < sizeof(PSF1Header)) return;

    auto psf1 = reinterpret_cast<const PSF1Header*>(data.data());
    if (psf1->magic == 0x0436) {
        m_is_psf2 = false;
        m_width = 8;
        m_height = psf1->charsize;
        m_charsize = psf1->charsize;
        m_headersize = sizeof(PSF1Header);
        m_valid = true;
        return;
    }

    if (data.size() < sizeof(PSF2Header)) return;
    auto psf2 = reinterpret_cast<const PSF2Header*>(data.data());
    if (psf2->magic == 0x864ab572) {
        m_is_psf2 = true;
        m_width = psf2->width;
        m_height = psf2->height;
        m_charsize = psf2->charsize;
        m_headersize = psf2->headersize;
        m_valid = true;
    }
}

const u8* Font::get_glyph(char c) const {
    if (!m_valid) return nullptr;
    u32 index = static_cast<u8>(c);
    return m_data.data() + m_headersize + (index * m_charsize);
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

void Font::draw_char(char c, u32 x, u32 y, u32 color, Style style) const {
    Framebuffer* fb = active_framebuffer();
    if (!fb) return;

    auto plot_glyph = [&](u32 ox, u32 oy) {
        if (!m_valid) {
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    if (legacy_glyph_pixel(c, row, col)) {
                        fb->put_pixel(ox + col, oy + row, color);
                    }
                }
            }
            return;
        }

        const u8* glyph = get_glyph(c);
        u32 bytes_per_line = (m_width + 7) / 8;

        for (u32 row = 0; row < m_height; row++) {
            for (u32 col = 0; col < m_width; col++) {
                u8 byte = glyph[row * bytes_per_line + (col / 8)];
                if ((byte >> (7 - (col % 8))) & 1) {
                    i32 shear = 0;
                    if (style == Style::Italic) {
                        shear = (m_height - row) / 4;
                    }
                    fb->put_pixel(ox + col + shear, oy + row, color);
                }
            }
        }
    };

    plot_glyph(x, y);
    if (style == Style::Bold) {
        plot_glyph(x + 1, y);
    }
}

void Font::draw_string(const char* str, u32 x, u32 y, u32 color, Alignment align, Style style, i32 spacing) const {
    if (!str) return;
    u32 char_w = m_valid ? m_width : 8;
    u32 char_h = m_valid ? m_height : 10;
    u32 cur_y = y;

    const char* line_start = str;
    while (*line_start) {
        const char* line_end = line_start;
        u32 line_len = 0;
        while (*line_end && *line_end != '\n') {
            line_len++;
            line_end++;
        }

        u32 total_w = line_len * (char_w + spacing);
        u32 start_x = x;
        if (align == Alignment::Center) {
            start_x = x - total_w / 2;
        } else if (align == Alignment::Right) {
            start_x = x - total_w;
        }

        for (u32 i = 0; i < line_len; i++) {
            draw_char(line_start[i], start_x + i * (char_w + spacing), cur_y, color, style);
        }

        cur_y += char_h;
        line_start = *line_end == '\n' ? line_end + 1 : line_end;
    }
}

void Font::set_default(Font* font) { g_default_font = font; }
Font* Font::get_default() { return g_default_font; }

void Font::measure_string_default(const char* str, u32& w, u32& h, i32 spacing) {
    if (g_default_font) g_default_font->measure_string(str, w, h, spacing);
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

void Font::draw_char_default(char c, u32 x, u32 y, u32 color, Style style) {
    if (g_default_font) g_default_font->draw_char(c, x, y, color, style);
    else {
        // Fallback draw_char with bold/italic simulation if needed
        // For simplicity, just use regular fallback
        Framebuffer* fb = active_framebuffer();
        if (!fb) return;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (legacy_glyph_pixel(c, row, col)) {
                    fb->put_pixel(x + col, y + row, color);
                    if (style == Style::Bold) fb->put_pixel(x + col + 1, y + row, color);
                }
            }
        }
    }
}

void Font::draw_string_default(const char* str, u32 x, u32 y, u32 color, Alignment align, Style style, i32 spacing) {
    if (g_default_font) g_default_font->draw_string(str, x, y, color, align, style, spacing);
    else {
        u32 cur_y = y;
        const char* line_start = str;
        while (line_start && *line_start) {
            const char* line_end = line_start;
            u32 line_len = 0;
            while (*line_end && *line_end != '\n') {
                line_len++;
                line_end++;
            }

            u32 total_w = line_len * (8 + spacing);
            u32 start_x = x;
            if (align == Alignment::Center) start_x = x - total_w / 2;
            else if (align == Alignment::Right) start_x = x - total_w;

            for (u32 i = 0; i < line_len; i++) {
                draw_char_default(line_start[i], start_x + i * (8 + spacing), cur_y, color, style);
            }

            cur_y += 10;
            line_start = *line_end == '\n' ? line_end + 1 : line_end;
        }
    }
}

} // namespace acos::graphics
