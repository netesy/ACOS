#include <kernel/graphics/surface.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::graphics {

Surface::Surface(u32 width, u32 height, bool double_buffered)
    : m_width(0), m_height(0), m_front_buffer(nullptr), m_back_buffer(nullptr), m_double_buffered(double_buffered) {

    if (width == 0 || height == 0 || width > MAX_DIMENSION || height > MAX_DIMENSION) {
        return;
    }

    u64 total_pixels = static_cast<u64>(width) * height;
    if (total_pixels > MAX_DIMENSION * MAX_DIMENSION) {
        return;
    }

    m_back_buffer = reinterpret_cast<u32*>(memory::kmalloc(total_pixels * sizeof(u32)));
    if (!m_back_buffer) {
        return;
    }
    memset(m_back_buffer, 0, total_pixels * sizeof(u32));

    if (m_double_buffered) {
        m_front_buffer = reinterpret_cast<u32*>(memory::kmalloc(total_pixels * sizeof(u32)));
        if (!m_front_buffer) {
            memory::kfree(m_back_buffer);
            m_back_buffer = nullptr;
            return;
        }
        memset(m_front_buffer, 0, total_pixels * sizeof(u32));
    } else {
        m_front_buffer = m_back_buffer;
    }

    m_width = width;
    m_height = height;
}

Surface::~Surface() {
    if (m_back_buffer) {
        memory::kfree(m_back_buffer);
    }
    if (m_double_buffered && m_front_buffer) {
        memory::kfree(m_front_buffer);
    }
}

void Surface::swap_buffers() {
    if (!is_valid() || !m_double_buffered || !m_front_buffer || !m_back_buffer) {
        return;
    }

    if (!m_dirty.is_empty()) {
        const ClipRect& rect = m_dirty.rect();
        // Constrain bounding box to surface dimensions
        i32 x1 = rect.x < 0 ? 0 : rect.x;
        i32 y1 = rect.y < 0 ? 0 : rect.y;
        i32 x2 = (rect.x + rect.w > (i32)m_width) ? (i32)m_width : (rect.x + rect.w);
        i32 y2 = (rect.y + rect.h > (i32)m_height) ? (i32)m_height : (rect.y + rect.h);

        if (x1 < x2 && y1 < y2) {
            for (i32 y = y1; y < y2; ++y) {
                for (i32 x = x1; x < x2; ++x) {
                    u32 idx = y * m_width + x;
                    m_front_buffer[idx] = m_back_buffer[idx];
                }
            }
        }
        m_dirty.reset();
    } else {
        // Direct copy of the entire buffer if no specific dirty tracking was done
        memcpy(m_front_buffer, m_back_buffer, m_width * m_height * sizeof(u32));
    }
}

void Surface::resize(u32 width, u32 height) {
    if (!is_valid()) return;
    if (width == 0 || height == 0 || width > MAX_DIMENSION || height > MAX_DIMENSION) return;
    if (width == m_width && height == m_height) return;

    u64 total_pixels = static_cast<u64>(width) * height;
    if (total_pixels > MAX_DIMENSION * MAX_DIMENSION) {
        return;
    }

    u32* new_back = reinterpret_cast<u32*>(memory::kmalloc(total_pixels * sizeof(u32)));
    if (!new_back) return;
    memset(new_back, 0, total_pixels * sizeof(u32));

    u32* new_front = nullptr;
    if (m_double_buffered) {
        new_front = reinterpret_cast<u32*>(memory::kmalloc(total_pixels * sizeof(u32)));
        if (!new_front) {
            memory::kfree(new_back);
            return;
        }
        memset(new_front, 0, total_pixels * sizeof(u32));
    }

    // Copy old content where overlapping
    u32 min_w = m_width < width ? m_width : width;
    u32 min_h = m_height < height ? m_height : height;

    if (m_back_buffer) {
        for (u32 y = 0; y < min_h; ++y) {
            for (u32 x = 0; x < min_w; ++x) {
                new_back[y * width + x] = m_back_buffer[y * m_width + x];
            }
        }
        memory::kfree(m_back_buffer);
    }

    if (m_double_buffered && m_front_buffer) {
        for (u32 y = 0; y < min_h; ++y) {
            for (u32 x = 0; x < min_w; ++x) {
                new_front[y * width + x] = m_front_buffer[y * m_width + x];
            }
        }
        memory::kfree(m_front_buffer);
    }

    m_back_buffer = new_back;
    if (m_double_buffered) {
        m_front_buffer = new_front;
    } else {
        m_front_buffer = new_back;
    }

    m_width = width;
    m_height = height;
    m_dirty.reset();
}

} // namespace acos::graphics
