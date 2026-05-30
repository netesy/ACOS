#pragma once
#include <acos/types.h>

namespace acos::graphics {

/**
 * Surface: Off-screen memory buffer for rendering.
 */
class Surface {
public:
    Surface(u32 width, u32 height);
    ~Surface();

    u32* buffer() { return m_buffer; }
    u32 width() const { return m_width; }
    u32 height() const { return m_height; }

private:
    u32 m_width;
    u32 m_height;
    u32* m_buffer;
};

} // namespace acos::graphics
