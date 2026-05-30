#include <acos/boot_info.h>

namespace acos::hal {

static FramebufferInfo* g_fb = nullptr;

static u8 font8x8_basic[128][8];

void font_init() {
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 8; j++) {
            font8x8_basic[i][j] = 0;
        }
    }
    // 'A'
    font8x8_basic['A'][0] = 0x18; font8x8_basic['A'][1] = 0x3C; font8x8_basic['A'][2] = 0x66;
    font8x8_basic['A'][3] = 0x7E; font8x8_basic['A'][4] = 0x66; font8x8_basic['A'][5] = 0x66;
    font8x8_basic['A'][6] = 0x66;
    // 'C'
    font8x8_basic['C'][0] = 0x3C; font8x8_basic['C'][1] = 0x66; font8x8_basic['C'][2] = 0x06;
    font8x8_basic['C'][3] = 0x06; font8x8_basic['C'][4] = 0x06; font8x8_basic['C'][5] = 0x66;
    font8x8_basic['C'][6] = 0x3C;
    // 'O'
    font8x8_basic['O'][0] = 0x3C; font8x8_basic['O'][1] = 0x66; font8x8_basic['O'][2] = 0x66;
    font8x8_basic['O'][3] = 0x66; font8x8_basic['O'][4] = 0x66; font8x8_basic['O'][5] = 0x66;
    font8x8_basic['O'][6] = 0x3C;
    // 'S'
    font8x8_basic['S'][0] = 0x3C; font8x8_basic['S'][1] = 0x66; font8x8_basic['S'][2] = 0x06;
    font8x8_basic['S'][3] = 0x3C; font8x8_basic['S'][4] = 0x60; font8x8_basic['S'][5] = 0x66;
    font8x8_basic['S'][6] = 0x3C;
}

static u32 g_cursor_x = 0;
static u32 g_cursor_y = 0;

void console_init(FramebufferInfo* fb) {
    g_fb = fb;
    g_cursor_x = 0;
    g_cursor_y = 0;
    font_init();
}

void console_put_pixel(u32 x, u32 y, u32 color) {
    if (!g_fb || x >= g_fb->width || y >= g_fb->height) return;
    u32* fb = reinterpret_cast<u32*>(g_fb->base);
    fb[y * g_fb->pitch + x] = color;
}

void console_putchar(char c, u32 x, u32 y, u32 color) {
    if (static_cast<u8>(c) >= 128) return;
    const u8* glyph = font8x8_basic[static_cast<u8>(c)];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (glyph[i] & (1 << (7 - j))) {
                console_put_pixel(x + j, y + i, color);
            }
        }
    }
}

void console_clear(u32 color) {
    if (!g_fb) return;
    for (u32 y = 0; y < g_fb->height; ++y) {
        for (u32 x = 0; x < g_fb->width; ++x) {
            console_put_pixel(x, y, color);
        }
    }
}

void console_print(const char* s, u32 color) {
    if (!g_fb) return;
    while (*s) {
        if (*s == '\n') {
            g_cursor_x = 0;
            g_cursor_y += 8;
        } else {
            console_putchar(*s, g_cursor_x, g_cursor_y, color);
            g_cursor_x += 8;
            if (g_cursor_x + 8 > g_fb->width) {
                g_cursor_x = 0;
                g_cursor_y += 8;
            }
        }

        if (g_cursor_y + 8 > g_fb->height) {
            console_clear(0x00000000);
            g_cursor_x = 0;
            g_cursor_y = 0;
        }
        s++;
    }
}

} // namespace acos::hal
