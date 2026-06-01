#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <kernel/graphics/graphics_manager.h>

namespace acos::shell {

DesktopShell::DesktopShell() : m_wallpaper_buffer(nullptr) {}

void DesktopShell::initialize() {
    gui::init_default_theme();
    
    // Initialize wallpaper
    acos::graphics::DisplayDevice* display = acos::graphics::GraphicsManager::primary_display();
    if (display) {
        acos::graphics::Framebuffer* fb = display->get_framebuffer();
        if (fb) {
            u32 width = fb->width();
            u32 height = fb->height();
            
            m_wallpaper_buffer = (u32*)acos::memory::kmalloc(width * height * sizeof(u32));
            if (m_wallpaper_buffer) {
                // Fill with gradient or pattern
                for (u32 y = 0; y < height; y++) {
                    for (u32 x = 0; x < width; x++) {
                        u32 color = 0x001E3A5F; // ACOS blue
                        m_wallpaper_buffer[y * width + x] = color;
                    }
                }
            }
        }
    }
}

void DesktopShell::run() {
    // Main shell event loop
    while (true) {
        // Process input events
        acos::input::InputEvent event;
        if (acos::input::InputManager::get_event(&event)) {
            // Route to appropriate handler
        }
        
        // Update display
        if (m_wallpaper_buffer) {
            acos::graphics::DisplayDevice* display = acos::graphics::GraphicsManager::primary_display();
            if (display) {
                acos::graphics::Framebuffer* fb = display->get_framebuffer();
                if (fb) {
                    // Composite wallpaper and windows
                }
            }
        }
        
        // Yield to other threads
        acos::scheduler::schedule();
    }
}

} // namespace acos::shell
