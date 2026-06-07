#include "taskbar.h"
#include <userland/gui/panel.h>
#include <userland/gui/theme.h>
#include <userland/gui/icon.h>
#include <userland/gui/text.h>
#include <userland/gui/core/flex.h>
#include <userland/gui/core/context.h>
#include "desktop_shell.h"

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 400, 50};
    m_clock_str[0] = '\0';
    set_glass(true);

    auto& region = gui::UIContext::get().region();

    auto root_layout = region.alloc<gui::widgets::Row>();
    root_layout->main_axis_alignment(gui::MainAxisAlignment::Center);
    root_layout->cross_axis_alignment(gui::CrossAxisAlignment::Center);
    root_layout->spacing(20);

    auto term_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Terminal);
    term_icon->on_click([](void*){ DesktopShell::get().launch_terminal(); });
    root_layout->add_child(term_icon.static_cast_to<gui::Widget>());

    auto file_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Files);
    file_icon->on_click([](void*){ DesktopShell::get().launch_file_manager(); });
    root_layout->add_child(file_icon.static_cast_to<gui::Widget>());

    auto code_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Code);
    root_layout->add_child(code_icon.static_cast_to<gui::Widget>());

    auto settings_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Settings);
    settings_icon->on_click([](void*){ DesktopShell::get().launch_settings(); });
    root_layout->add_child(settings_icon.static_cast_to<gui::Widget>());

    add_child(root_layout.static_cast_to<gui::Widget>());
}

void Taskbar::update_clock() {}

gui::Ref<gui::RenderObject> Taskbar::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void Taskbar::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
