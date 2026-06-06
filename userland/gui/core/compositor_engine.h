#pragma once
#include "software_compositor.h"
#include "vector.h"

namespace acos::gui {

class SoftwareCompositor {
public:
    SoftwareCompositor(::acos::u32* display_buffer, ::acos::u32 width, ::acos::u32 height)
        : m_display_buffer(display_buffer), m_width(width), m_height(height) {}

    void add_layer(SoftwareLayer* layer) {
        m_layers.push_back(layer);
    }

    void composite();

private:
    ::acos::u32* m_display_buffer;
    ::acos::u32 m_width, m_height;
    ::acos::Vector<SoftwareLayer*> m_layers;

    static ::acos::u32 blend(::acos::u32 dst, ::acos::u32 src, float opacity);
};

} // namespace acos::gui
