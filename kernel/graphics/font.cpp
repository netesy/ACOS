#include <kernel/graphics/font.h>
#include <kernel/graphics/graphics_manager.h>

namespace acos::graphics {

namespace {

bool glyph_pixel(char c, int row, int col) {
    const u8 ch = static_cast<u8>(c);
    if (ch <= 0x20) {
        return false;
    }
    if (row == 0 || row == 7 || col == 0 || col == 7) {
        return true;
    }
    const u8 pattern = static_cast<u8>((ch >> ((row + col) & 3)) ^ (ch << ((row ^ col) & 1)));
    return ((pattern >> (col & 7)) & 1U) != 0;
}

Framebuffer* active_framebuffer() {
    DisplayDevice* display = GraphicsManager::primary_display();
    return display ? display->get_framebuffer() : nullptr;
}

} // namespace

void Font::draw_char(char c, u32 x, u32 y, u32 color) {
    Framebuffer* fb = active_framebuffer();
    if (!fb) {
        return;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph_pixel(c, row, col)) {
                fb->put_pixel(x + static_cast<u32>(col), y + static_cast<u32>(row), color);
            }
        }
    }
}

void Font::draw_string(const char* str, u32 x, u32 y, u32 color) {
    if (!str) return;

    u32 cur_x = x;
    u32 cur_y = y;
    constexpr u32 line_height = 10;
    constexpr u32 max_width = 1920;

    while (*str) {
        char c = *str++;
        if (c == '\n') {
            cur_x = x;
            cur_y += line_height;
            continue;
        }
        if (c == '\t') {
            cur_x += 32;
            continue;
        }
        if (static_cast<u8>(c) < 32) continue;
        if (cur_x + 8 > max_width) {
            cur_x = x;
            cur_y += line_height;
        }
        draw_char(c, cur_x, cur_y, color);
        cur_x += 8;
    }
}

} // namespace acos::graphics
