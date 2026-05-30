#include <acos/boot_info.h>

namespace acos::hal {

static FramebufferInfo* g_fb = nullptr;

void console_init(FramebufferInfo* fb) {
    g_fb = fb;
}

void console_put_pixel(u32 x, u32 y, u32 color) {
    if (!g_fb || x >= g_fb->width || y >= g_fb->height) return;

    u32* fb = reinterpret_cast<u32*>(g_fb->base);
    fb[y * g_fb->pitch + x] = color;
}

// Simple 8x8 font implementation (placeholder)
// In a real system, we would load a font from the initrd or use a built-in one.
void console_putchar([[maybe_unused]] char c, u32 x, u32 y, u32 color) {
    // Very basic placeholder: just draw a square for now
    for (u32 i = 0; i < 8; ++i) {
        for (u32 j = 0; j < 8; ++j) {
            console_put_pixel(x + i, y + j, color);
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

} // namespace acos::hal
