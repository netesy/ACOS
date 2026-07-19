#pragma once
#include <acos/types.h>
#include "dirty_region.h"

namespace acos::graphics {

/**
 * Surface: Off-screen memory buffer for rendering supporting double buffering.
 */
class Surface {
public:
    static constexpr u32 MAX_DIMENSION = 4096;

    Surface(u32 width, u32 height, bool double_buffered = true);
    ~Surface();

    u32* buffer() { return m_back_buffer; }
    u32* front_buffer() { return m_front_buffer; }
    u32* back_buffer() { return m_back_buffer; }

    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    bool is_double_buffered() const { return m_double_buffered; }
    bool is_valid() const { return m_width > 0 && m_height > 0 && m_back_buffer != nullptr; }

    void swap_buffers();
    void resize(u32 width, u32 height);

    DirtyRegion& dirty_region() { return m_dirty; }
    const DirtyRegion& dirty_region() const { return m_dirty; }

private:
    u32 m_width;
    u32 m_height;
    u32* m_front_buffer;
    u32* m_back_buffer;
    bool m_double_buffered;
    DirtyRegion m_dirty;
};

} // namespace acos::graphics
