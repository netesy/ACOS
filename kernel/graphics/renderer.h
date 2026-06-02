#pragma once
#include <kernel/graphics/framebuffer.h>
#include <kernel/graphics/font.h>

namespace acos::graphics {

class Renderer {
public:
    Renderer(Framebuffer* fb);

    // Basic drawing
    void draw_pixel(u32 x, u32 y, u32 color);
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);

    // Text drawing
    void draw_text(const char* text, u32 x, u32 y, u32 color,
                   Font::Alignment align = Font::Alignment::Left,
                   Font::Style style = Font::Style::Regular,
                   i32 spacing = 0);
    
    // Advanced drawing
    void draw_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void fill_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color);
    void fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color);
    void draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad);
    void draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness);
    
    // Blending and effects
    void blend_pixel(u32 x, u32 y, u32 color, u8 alpha);
    void blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha);
    void draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha);
    
    // Clipping
    void set_clip_rect(const ClipRect& rect);
    void clear_clip_rect();

private:
    Framebuffer* m_fb;
};

} // namespace acos::graphics
