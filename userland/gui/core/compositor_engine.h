#pragma once
#include "software_compositor.h"
#include "vector.h"

namespace acos::gui {

class SoftwareCompositor {
public:
    SoftwareCompositor(u32* display_buffer, u32 width, u32 height)
        : m_display_buffer(display_buffer), m_width(width), m_height(height) {}

    void add_layer(SoftwareLayer* layer) {
        m_layers.push_back(layer);
    }

    void composite();

private:
    u32* m_display_buffer;
    u32 m_width, m_height;
    acos::Vector<SoftwareLayer*> m_layers;

    static u32 blend(u32 dst, u32 src, float opacity);
};

} // namespace acos::gui
