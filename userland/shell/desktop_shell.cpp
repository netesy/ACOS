#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <kernel/graphics/graphics_manager.h>
#include <kernel/graphics/renderer.h>
#include <kernel/memory/heap.h>
#include <kernel/input/input_manager.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::shell {

DesktopShell::DesktopShell() : m_wallpaper_buffer(nullptr) {}

void DesktopShell::initialize() {
    gui::init_default_theme();

    acos::graphics::DisplayDevice* display = acos::graphics::GraphicsManager::primary_display();
    if (!display) {
        return;
    }

    acos::graphics::Framebuffer* fb = display->get_framebuffer();
    if (!fb) {
        return;
    }

    const u32 width = fb->width();
    const u32 height = fb->height();
    m_wallpaper_buffer = (u32*)acos::memory::kmalloc(width * height * sizeof(u32));
    if (m_wallpaper_buffer) {
        for (u32 y = 0; y < height; ++y) {
            for (u32 x = 0; x < width; ++x) {
                const u32 blue = 0x3A + ((y * 0x40) / (height ? height : 1));
                const u32 green = 0x1E + ((x * 0x20) / (width ? width : 1));
                m_wallpaper_buffer[y * width + x] = 0xFF000000 | (green << 8) | blue;
            }
        }
    }

    acos::graphics::Renderer renderer(fb);
    if (m_wallpaper_buffer) {
        for (u32 y = 0; y < height; ++y) {
            for (u32 x = 0; x < width; ++x) {
                fb->put_pixel(x, y, m_wallpaper_buffer[y * width + x]);
            }
        }
    } else {
        renderer.fill_rect(0, 0, width, height, gui::g_current_theme.background);
    }

    renderer.draw_text("ACOS", 32, 32, gui::g_current_theme.text);
    renderer.draw_text("Adaptive Capability Operating System", 32, 52, gui::g_current_theme.text_secondary);
    renderer.fill_rounded_rect(32, 88, 360, 160, 10, 0xCC102A44);
    renderer.draw_border(32, 88, 360, 160, gui::g_current_theme.accent_light, 2);
    renderer.draw_text("Phase 11 Graphics Foundation", 52, 112, gui::g_current_theme.text);
    renderer.draw_text("Software renderer online", 52, 140, gui::g_current_theme.success);
    renderer.draw_text("Input router initialized", 52, 160, gui::g_current_theme.info);
    renderer.draw_text("Capability display resources ready", 52, 180, gui::g_current_theme.warning);

    m_taskbar.set_position(0, height > 40 ? static_cast<i32>(height - 40) : 0);
    m_taskbar.set_size(static_cast<i32>(width), 40);
    m_taskbar.draw(&renderer);

    m_launcher.set_position(32, height > 460 ? static_cast<i32>(height - 460) : 260);
    m_launcher.show();
    m_launcher.draw(&renderer);

    m_notifications.post_notification("ACOS", "GUI smoke frame rendered");
    m_notifications.draw(&renderer);
}

void DesktopShell::run() {
    // Initial desktop frame already rendered in initialize().
    // Return immediately so kernelMain can enter its idle loop.
    // In a fully scheduled system, input/event processing would be
    // driven by the scheduler via periodic tick callbacks.
}

} // namespace acos::shell
