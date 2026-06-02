#include "desktop_shell.h"
#include <userland/gui/theme.h>

namespace acos::shell {

DesktopShell::DesktopShell() {
    gui::init_synthetic_theme();
}

void DesktopShell::initialize() {}
void DesktopShell::run() {}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    acos::graphics::Gradient bg_grad;
    bg_grad.start = acos::graphics::Color(10, 10, 11);
    bg_grad.end = acos::graphics::Color(26, 18, 38);
    bg_grad.horizontal = false;
    renderer->draw_gradient_rect(0, 0, 800, 600, bg_grad);

    renderer->fill_circle(0, 0, 200, 0x1A00E5FF);
    renderer->fill_circle(800, 600, 300, 0x1ABF00FF);

    m_taskbar.draw(renderer);
    m_launcher.draw(renderer);
    m_notifications.draw(renderer);
}

} // namespace acos::shell
