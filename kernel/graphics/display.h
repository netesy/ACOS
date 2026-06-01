#pragma once
#include <acos/types.h>
#include <kernel/graphics/framebuffer.h>

namespace acos::graphics {

// Color utilities
struct Color {
    u8 r, g, b, a;
    
    Color() : r(0), g(0), b(0), a(255) {}
    Color(u8 r, u8 g, u8 b, u8 a = 255) : r(r), g(g), b(b), a(a) {}
    
    u32 to_argb() const {
        return ((u32)a << 24) | ((u32)r << 16) | ((u32)g << 8) | b;
    }
    
    static Color from_argb(u32 argb) {
        return Color((argb >> 16) & 0xFF, (argb >> 8) & 0xFF, argb & 0xFF, (argb >> 24) & 0xFF);
    }
};

// Gradient support
struct Gradient {
    Color start;
    Color end;
    bool horizontal;
};

// Clipping rectangle
struct ClipRect {
    i32 x, y, w, h;
    
    bool intersects(i32 px, i32 py) const {
        return px >= x && px < x + w && py >= y && py < y + h;
    }
};

class DisplayDevice {
public:
    virtual ~DisplayDevice() = default;
    virtual bool initialize() = 0;
    virtual Framebuffer* get_framebuffer() = 0;
    virtual u32 width() const = 0;
    virtual u32 height() const = 0;
};

} // namespace acos::graphics
