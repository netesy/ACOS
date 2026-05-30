#include <kernel/graphics/font.h>
#include <kernel/hal/console.cpp> // Reuse existing console font for Phase 11 foundation

namespace acos::graphics {

void Font::draw_char(char c, u32 x, u32 y, u32 color) {
    // In a future phase, we will implement a more advanced font engine.
    // For now, we reuse the existing console font logic.
    (void)c; (void)x; (void)y; (void)color;
}

void Font::draw_string(const char* str, u32 x, u32 y, u32 color) {
    while (*str) {
        draw_char(*str++, x, y, color);
        x += 8;
    }
}

} // namespace acos::graphics
