#include <kernel/graphics/graphics_manager.h>

namespace acos::graphics {

DisplayDevice* GraphicsManager::g_displays[4];
u32 GraphicsManager::g_display_count = 0;

void GraphicsManager::register_display(DisplayDevice* display) {
    if (g_display_count < 4) {
        g_displays[g_display_count++] = display;
    }
}

DisplayDevice* GraphicsManager::primary_display() {
    if (g_display_count > 0) return g_displays[0];
    return nullptr;
}

void GraphicsManager::init() {}

} // namespace acos::graphics
