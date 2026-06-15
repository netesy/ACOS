#pragma once
#include <acos/types.h>

namespace acos::graphics {

struct FramebufferInfo {
    u64 base;
    u64 size;
    u32 width;
    u32 height;
    u32 pitch;
    u32 bpp;
};

u64 create_surface(u32 width, u32 height);
u64 create_window(u32 width, u32 height, const char* title);
void present(u64 handle);
void* get_framebuffer();
bool get_framebuffer_info(FramebufferInfo* info);

} // namespace acos::graphics
