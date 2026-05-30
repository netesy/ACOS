#pragma once
#include <acos/types.h>

namespace acos::graphics {

class Font {
public:
    static void draw_char(char c, u32 x, u32 y, u32 color);
    static void draw_string(const char* str, u32 x, u32 y, u32 color);
};

} // namespace acos::graphics
