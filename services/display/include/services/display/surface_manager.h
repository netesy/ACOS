#pragma once
#include <acos/types.h>

namespace acos::display {

struct Surface {
    u64 id;
    u64 owner_pid;
    u32 width;
    u32 height;
    u32* buffer;
    u32* back_buffer;
    bool double_buffered;
};

class SurfaceManager {
public:
    SurfaceManager();
    ~SurfaceManager();

    Surface* create_surface(u64 owner_pid, u32 width, u32 height, bool double_buffered = true);
    void destroy_surface(u64 id);
    Surface* get_surface(u64 id);

    bool swap_buffers(u64 id);

private:
    static constexpr usize MAX_SURFACES = 256;
    Surface m_surfaces[MAX_SURFACES];
    usize m_surface_count;
};

} // namespace acos::display
