#pragma once
#include <acos/types.h>

namespace acos::ui {

struct Color {
    u8 r, g, b, a;
    Color(u8 r, u8 g, u8 b, u8 a = 255) : r(r), g(g), b(b), a(a) {}
    static constexpr u32 White = 0xFFFFFFFF;
    static constexpr u32 Blue = 0xFF0000FF;
    static constexpr u32 Black = 0x000000FF;
    u32 to_argb() const { return (a << 24) | (r << 16) | (g << 8) | b; }
};

} // namespace acos::ui
