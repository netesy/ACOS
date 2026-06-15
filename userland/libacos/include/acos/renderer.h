#pragma once
#include <acos/types.h>
#include <acos/framebuffer.h>
#include <acos/graphics_types.h>

namespace acos::graphics {

class Renderer {
public:
    Renderer(Framebuffer* fb);

    void draw_pixel(u32 x, u32 y, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void blend_pixel(u32 x, u32 y, u32 color, u8 alpha);

    u32 width() const { return m_fb ? m_fb->width() : 0; }
    u32 height() const { return m_fb ? m_fb->height() : 0; }

private:
    Framebuffer* m_fb;
};

} // namespace acos::graphics
