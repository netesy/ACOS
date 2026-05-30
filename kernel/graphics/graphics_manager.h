#pragma once
#include <kernel/graphics/display.h>

namespace acos::graphics {

class GraphicsManager {
public:
    static void register_display(DisplayDevice* display);
    static DisplayDevice* primary_display();
    static void init();

private:
    static DisplayDevice* g_displays[4];
    static u32 g_display_count;
};

} // namespace acos::graphics
