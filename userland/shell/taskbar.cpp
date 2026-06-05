#include "taskbar.h"
#include <userland/gui/theme.h>
#include <userland/gui/icon.h>
#include <userland/gui/text.h>
#include <userland/gui/core/flex.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 800, 48};
    m_clock_str[0] = '\0';
    set_glass(true);

    auto& region = gui::UIContext::get().region();

    auto root_layout = region.alloc<gui::widgets::Row>();
    root_layout->cross_axis_alignment(gui::CrossAxisAlignment::Center);

    auto terminal_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Terminal);
    auto files_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Files);
    auto code_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Code);
    code_icon->set_active(true);
    auto settings_icon = region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Settings);

    root_layout->add_child(terminal_icon);
    root_layout->add_child(files_icon);
    root_layout->add_child(code_icon);
    root_layout->add_child(settings_icon);

    auto clock = region.alloc<gui::widgets::Text>("12:00 PM");
    root_layout->add_child(clock);

    auto volume = region.alloc<VolumeIndicator>();
    root_layout->add_child(volume);

    add_child(root_layout);
}

void Taskbar::update_clock() {
    // ...
}

gui::Ref<gui::RenderObject> Taskbar::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void Taskbar::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
