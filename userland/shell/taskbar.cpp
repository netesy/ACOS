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
    m_rect = {0, 0, 400, 50};
    m_clock_str[0] = '\0';
    set_glass(true);

    auto& region = gui::UIContext::get().region();

    auto root_layout = region.alloc<gui::widgets::Row>();
    root_layout->main_axis_alignment(gui::MainAxisAlignment::SpaceBetween);
    root_layout->cross_axis_alignment(gui::CrossAxisAlignment::Center);
    root_layout->spacing(0);

    // Left section: Start button
    auto left_section = region.alloc<gui::widgets::Row>();
    left_section->spacing(8);
    left_section->cross_axis_alignment(gui::CrossAxisAlignment::Center);
    
    auto start_button = region.alloc<gui::widgets::Panel>();
    start_button->set_rect({0, 0, 48, 48});
    start_button->set_background_color(0);
    start_button->radius(gui::g_current_theme.widget_radius + 4);
    start_button->elevation(2);
    start_button->padding(4, 4, 4, 4);
    
    auto start_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Monitor);
    start_icon->set_rect({4, 4, 40, 40});
    start_icon->radius(gui::g_current_theme.widget_radius);
    start_icon->on_click([](void*){ DesktopShell::get().toggle_launcher(); });
    start_icon->set_animate_on_hover(true);
    start_button->add_child(start_icon.static_cast_to<gui::Widget>());
    
    left_section->add_child(start_button.static_cast_to<gui::Widget>());

    // Center section: App icons
    auto center_section = region.alloc<gui::widgets::Row>();
    center_section->spacing(12);
    center_section->cross_axis_alignment(gui::CrossAxisAlignment::Center);

    auto create_dock_item = [&](gui::widgets::IconType type, void (*callback)(void*)) {
        auto container = region.alloc<gui::widgets::Panel>();
        container->set_rect({0, 0, 52, 52});
        container->set_background_color(0);
        container->radius(gui::g_current_theme.widget_radius + 4);
        container->elevation(2);
        container->padding(4, 4, 4, 4);

        auto icon = region.alloc<gui::widgets::Icon>(type);
        icon->set_rect({4, 4, 44, 44});
        icon->radius(gui::g_current_theme.widget_radius + 2);
        icon->on_click(callback);
        icon->set_animate_on_hover(true);
        container->add_child(icon.static_cast_to<gui::Widget>());

        // Visual indicator (dot) for running app
        auto indicator = region.alloc<gui::widgets::Panel>();
        indicator->set_rect({20, 46, 6, 4});
        indicator->radius(2);
        indicator->set_background_color(gui::g_current_theme.primary);
        indicator->set_visible(true);
        container->add_child(indicator.static_cast_to<gui::Widget>());

        return container.static_cast_to<gui::Widget>();
    };

    center_section->add_child(create_dock_item(gui::widgets::IconType::Terminal, [](void*){ DesktopShell::get().launch_terminal(); }));
    center_section->add_child(create_dock_item(gui::widgets::IconType::Files, [](void*){ DesktopShell::get().launch_file_manager(); }));
    center_section->add_child(create_dock_item(gui::widgets::IconType::Settings, [](void*){ DesktopShell::get().launch_settings(); }));

    // Right section: System tray
    auto right_section = region.alloc<gui::widgets::Row>();
    right_section->spacing(12);
    right_section->cross_axis_alignment(gui::CrossAxisAlignment::Center);
    
    auto power_button = region.alloc<gui::widgets::Panel>();
    power_button->set_rect({0, 0, 48, 48});
    power_button->set_background_color(0);
    power_button->radius(gui::g_current_theme.widget_radius + 4);
    power_button->elevation(2);
    power_button->padding(4, 4, 4, 4);
    
    auto power_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Power);
    power_icon->set_rect({4, 4, 40, 40});
    power_icon->radius(gui::g_current_theme.widget_radius);
    power_icon->on_click([](void*){
        acos::process::log("Shutting down Asade from Taskbar Power Button...\n");
        acos::process::exit(0);
    });
    power_icon->set_animate_on_hover(true);
    power_button->add_child(power_icon.static_cast_to<gui::Widget>());
    
    right_section->add_child(power_button.static_cast_to<gui::Widget>());

    root_layout->add_child(left_section.static_cast_to<gui::Widget>());
    root_layout->add_child(center_section.static_cast_to<gui::Widget>());
    root_layout->add_child(right_section.static_cast_to<gui::Widget>());

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
