#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include "taskbar.h"
#include "launcher.h"

namespace acos::shell {

static Launcher* s_launcher = nullptr;

[[maybe_unused]] static void toggle_launcher(void*) {
    if (s_launcher) {
        if (s_launcher->is_visible()) s_launcher->hide();
        else s_launcher->show();
    }
}

DesktopShell::DesktopShell() {
    gui::widgets::init_synthetic_theme();
}

void DesktopShell::initialize() {
    auto& region = m_ui_context.region();
    auto root = region.alloc<gui::widgets::Panel>();
    root->set_rect({0, 0, 1024, 768});

    auto taskbar = region.alloc<Taskbar>();
    auto launcher = region.alloc<Launcher>();
    s_launcher = launcher.operator->();

    root->add_child(taskbar.static_cast_to<gui::Widget>());
    root->add_child(launcher.static_cast_to<gui::Widget>());

    m_ui_context.set_root(root.static_cast_to<gui::Widget>());
}

void DesktopShell::run() {}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    acos::graphics::Gradient bg_grad;
    bg_grad.start = acos::graphics::Color(10, 10, 11);
    bg_grad.end = acos::graphics::Color(26, 18, 38);
    bg_grad.horizontal = false;
    renderer->draw_gradient_rect(0, 0, renderer->width(), renderer->height(), bg_grad);

    m_ui_context.paint(renderer);
}

} // namespace acos::shell
