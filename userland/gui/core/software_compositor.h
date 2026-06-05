#pragma once
#include "compositor.h"
#include <acos/runtime.h>

namespace acos::gui {

class SoftwareSurface : public Surface {
public:
    SoftwareSurface(u32 w, u32 h) : m_width(w), m_height(h) {
        m_buffer = new u32[w * h];
        for (u32 i = 0; i < w * h; i++) m_buffer[i] = 0;
    }
    ~SoftwareSurface() override { delete[] m_buffer; }

    void* map() override { return m_buffer; }
    void unmap() override {}
    u32 width() const override { return m_width; }
    u32 height() const override { return m_height; }

    u32* buffer() { return m_buffer; }

private:
    u32* m_buffer;
    u32 m_width, m_height;
};

class SoftwareLayer : public CompositorLayer {
public:
    SoftwareLayer() : m_x(0), m_y(0), m_opacity(1.0f), m_surface(nullptr) {}

    void set_position(i32 x, i32 y) override { m_x = x; m_y = y; }
    void set_opacity(float opacity) override { m_opacity = opacity; }
    void set_surface(Surface* surface) override { m_surface = static_cast<SoftwareSurface*>(surface); }
    void commit() override { /* Notify compositor if necessary */ }

    i32 x() const { return m_x; }
    i32 y() const { return m_y; }
    float opacity() const { return m_opacity; }
    SoftwareSurface* surface() const { return m_surface; }

private:
    i32 m_x, m_y;
    float m_opacity;
    SoftwareSurface* m_surface;
};

} // namespace acos::gui
