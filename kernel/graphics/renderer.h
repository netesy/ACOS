#pragma once
#include <kernel/graphics/framebuffer.h>

namespace acos::graphics {

class Renderer {
public:
    Renderer(Framebuffer* fb);

    void draw_pixel(u32 x, u32 y, u32 color);
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void draw_text(const char* text, u32 x, u32 y, u32 color);

private:
    Framebuffer* m_fb;
};

} // namespace acos::graphics
