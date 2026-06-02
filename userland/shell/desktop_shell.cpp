#include "desktop_shell.h"
#include <userland/gui/theme.h>

namespace acos::shell {

DesktopShell::DesktopShell() {
    gui::init_synthetic_theme();
}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    // The compositor now clears to #0A0A0B, so we can draw decorations
    // Wallpaper/Atmosphere
    acos::graphics::Gradient bg_grad;
    bg_grad.start = acos::graphics::Color(10, 10, 11);
    bg_grad.end = acos::graphics::Color(26, 18, 38);
    bg_grad.horizontal = false;
    renderer->draw_gradient_rect(0, 0, 800, 600, bg_grad);

    // Subtle neon glows in corners
    renderer->fill_circle(0, 0, 200, 0x1A00E5FF);
    renderer->fill_circle(800, 600, 300, 0x1ABF00FF);

    m_taskbar.draw(renderer);
    m_launcher.draw(renderer);
    m_notification_center.draw(renderer);
}

} // namespace acos::shell
