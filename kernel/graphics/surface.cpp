#include <kernel/graphics/surface.h>
#include <kernel/memory/heap.h>

namespace acos::graphics {

Surface::Surface(u32 width, u32 height) : m_width(width), m_height(height) {
    m_buffer = reinterpret_cast<u32*>(memory::kmalloc(width * height * 4));
}

Surface::~Surface() {
    // kfree(m_buffer);
}

} // namespace acos::graphics
