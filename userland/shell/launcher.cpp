#include <acos/process.h>
#include <acos/runtime.h>
#include "launcher.h"
#include <acos/renderer.h>
#include <userland/gui/theme.h>
#include <userland/gui/text.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

Launcher::Launcher() {
    m_rect = {10, 10, 200, 300};
    m_active = false;
    set_glass(true);
    set_visible(false);

    auto& region = gui::UIContext::get().region();
    auto title = region.alloc<gui::widgets::Text>("Applications");
    add_child(title);
}

void Launcher::show() { set_visible(true); m_active = true; }
void Launcher::hide() { set_visible(false); m_active = false; }

gui::Ref<gui::RenderObject> Launcher::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void Launcher::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
