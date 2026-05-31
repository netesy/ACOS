#include <acos/boot_info.h>
#include <kernel/hal/console.h>

namespace acos::hal {

static FramebufferInfo* g_fb = nullptr;

static u8 font8x8_basic[128][8];

void font_init() {
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 8; j++) {
            font8x8_basic[i][j] = 0;
        }
    }
    font8x8_basic['A'][0] = 0x18; font8x8_basic['A'][1] = 0x3C; font8x8_basic['A'][2] = 0x66;
    font8x8_basic['A'][3] = 0x7E; font8x8_basic['A'][4] = 0x66; font8x8_basic['A'][5] = 0x66;
    font8x8_basic['A'][6] = 0x66;
}

void console_init(FramebufferInfo* fb) {
    g_fb = fb;
    font_init();
}

void console_put_pixel(u32 x, u32 y, u32 color) {
    if (!g_fb) return;
    u32* fb_ptr = (u32*)g_fb->base;
    fb_ptr[y * g_fb->width + x] = color;
}

void console_putchar(char c, u32 x, u32 y, u32 color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (font8x8_basic[(u8)c][i] & (1 << j)) {
                console_put_pixel(x + j, y + i, color);
            }
        }
    }
}

void console_clear(u32 color) {
    if (!g_fb) return;
    u32* fb_ptr = (u32*)g_fb->base;
    for (u32 i = 0; i < g_fb->width * g_fb->height; i++) {
        fb_ptr[i] = color;
    }
}

static u32 cursor_x = 0;
static u32 cursor_y = 0;

void console_print(const char* s, u32 color) {
    while (*s) {
        if (*s == '\n') {
            cursor_x = 0;
            cursor_y += 10;
        } else {
            console_putchar(*s, cursor_x, cursor_y, color);
            cursor_x += 8;
            if (g_fb && cursor_x + 8 > g_fb->width) {
                cursor_x = 0;
                cursor_y += 10;
            }
        }
        s++;
    }
}

} // namespace acos::hal
