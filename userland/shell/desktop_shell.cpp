#include "desktop_shell.h"
#include <ui/context.h>

namespace acos::shell {

DesktopShell::DesktopShell() {
}

void DesktopShell::initialize() {}
void DesktopShell::run() {}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    u32 w = renderer->width();
    u32 h = renderer->height();
    if (w == 0 || h == 0) return;

    acos::graphics::Gradient bg_grad;
    bg_grad.start = acos::graphics::Color(10, 10, 11);
    bg_grad.end = acos::graphics::Color(26, 18, 38);
    bg_grad.horizontal = false;
    renderer->draw_gradient_rect(0, 0, w, h, bg_grad);

    renderer->fill_circle(0, 0, 200, 0x1A00E5FF);
    renderer->fill_circle(w, h, 300, 0x1ABF00FF);

    // In the new system, DesktopShell would own a UIContext
    // and would call ctx.paint(renderer) which would handle drawing all widgets.
    // For now, we keep the structure but actual drawing is a no-op until
    // the system is further implemented.
}

} // namespace acos::shell
