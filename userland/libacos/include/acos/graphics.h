#pragma once
#include <acos/types.h>
#include <acos/abi/display.h>

namespace acos::graphics {

struct FramebufferInfo {
    u64 base;
    u64 size;
    u32 width;
    u32 height;
    u32 pitch;
    u32 bpp;
};

using DisplayMsg = abi::DisplayMsg;
using DisplayMsgType = abi::DisplayMsgType;

u64 create_surface(u32 width, u32 height);
u64 create_window(u32 width, u32 height, const char* title);
void present(u64 handle);
void* get_framebuffer();
bool get_framebuffer_info(FramebufferInfo* info);

void send_command_to_ds(const DisplayMsg& msg);

} // namespace acos::graphics
