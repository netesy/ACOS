#include <acos/process.h>
#include <acos/runtime.h>
#include "taskbar.h"
#include <acos/renderer.h>
#include <userland/gui/panel.h>
#include <userland/gui/theme.h>
#include <userland/gui/icon.h>
#include <userland/gui/text.h>
#include <userland/gui/core/flex.h>
#include <userland/gui/core/context.h>
#include "desktop_shell.h"

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 504, 56}; // Fit the expanded inner dock container bounds
    m_clock_str[0] = '\0';
    set_glass(false);
    set_background_color(0); // Transparent inner container so dock background is uniform

    auto& region = gui::UIContext::get().region();

    auto root_layout = region.alloc<gui::widgets::Row>();
    root_layout->main_axis_alignment(gui::MainAxisAlignment::Center);
    root_layout->cross_axis_alignment(gui::CrossAxisAlignment::Center);
    root_layout->spacing(32); // Beautiful, cleanly spaced icons!

    auto create_dock_item = [&](gui::widgets::IconType type, void (*callback)(void*)) {
        auto container = region.alloc<gui::widgets::Panel>();
        container->set_rect({0, 0, 48, 48});
        container->set_background_color(0);

        auto icon = region.alloc<gui::widgets::Icon>(type);
        icon->set_rect({4, 4, 40, 40});
        icon->on_click(callback);
        container->add_child(icon.static_cast_to<gui::Widget>());

        // Visual indicator (dot) for running app
        auto indicator = region.alloc<gui::widgets::Panel>();
        indicator->set_rect({22, 44, 4, 4}); // Perfectly positioned indicator dot
        indicator->radius(2);
        indicator->set_background_color(0xFFFFFFFF);
        indicator->set_visible(true); // Should be dynamic based on process state
        container->add_child(indicator.static_cast_to<gui::Widget>());

        return container.static_cast_to<gui::Widget>();
    };

    root_layout->add_child(create_dock_item(gui::widgets::IconType::Terminal, [](void*){ DesktopShell::get().launch_terminal(); }));
    root_layout->add_child(create_dock_item(gui::widgets::IconType::Files, [](void*){ DesktopShell::get().launch_file_manager(); }));
    root_layout->add_child(create_dock_item(gui::widgets::IconType::Monitor, [](void*){ DesktopShell::get().toggle_launcher(); }));
    root_layout->add_child(create_dock_item(gui::widgets::IconType::Settings, [](void*){ DesktopShell::get().launch_settings(); }));
    root_layout->add_child(create_dock_item(gui::widgets::IconType::Battery, [](void*){
        acos::process::log("Shutting down Asade from Taskbar Power Button...\n");
        acos::process::exit(0);
    }));

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
