#pragma once
#include <acos/boot_info.h>

namespace acos::hal {
    void console_init(FramebufferInfo* fb);
    void console_clear(u32 color);
    void console_print(const char* s, u32 color = 0xFFFFFFFF);
}
