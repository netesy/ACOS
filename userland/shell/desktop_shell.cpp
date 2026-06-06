#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include <userland/gui/panel.h>
#include <userland/gui/text.h>
#include <userland/gui/listview.h>
#include <userland/gui/progressbar.h>
#include <userland/gui/graph.h>
#include <userland/gui/badge.h>
#include <userland/gui/icon.h>
#include <userland/gui/core/flex.h>
#include "taskbar.h"
#include "launcher.h"

namespace acos::shell {

DesktopShell::DesktopShell() {
    gui::widgets::init_synthetic_theme();
}

void DesktopShell::initialize() {
    auto& region = m_ui_context.region();

    // Main Root Panel
    auto root = region.alloc<gui::widgets::Panel>();
    root->set_rect({0, 0, 1024, 768});
    root->set_background_color(0xFF0A0A0B);

    // Top Bar
    auto top_bar = region.alloc<gui::widgets::Panel>();
    top_bar->set_rect({0, 0, 1024, 40});
    top_bar->set_background_color(0x33000000);

    auto top_layout = region.alloc<gui::widgets::Row>();
    top_layout->set_rect({20, 0, 984, 40});
    top_layout->cross_axis_alignment(gui::CrossAxisAlignment::Center);

    top_layout->add_child(region.alloc<gui::widgets::Text>("ACOS_KERNEL").static_cast_to<gui::Widget>());
    top_layout->add_child(region.alloc<gui::widgets::Text>("System").static_cast_to<gui::Widget>());
    top_layout->add_child(region.alloc<gui::widgets::Text>("Network").static_cast_to<gui::Widget>());
    top_layout->add_child(region.alloc<gui::widgets::Text>("Security").static_cast_to<gui::Widget>());

    auto spacer = region.alloc<gui::widgets::Panel>(); // Empty spacer
    top_layout->add_child(spacer.static_cast_to<gui::Widget>());

    top_layout->add_child(region.alloc<gui::widgets::Text>("127.0.0.1").static_cast_to<gui::Widget>());
    top_layout->add_child(region.alloc<gui::widgets::Text>("OCT 24, 04:20:01").static_cast_to<gui::Widget>());

    top_bar->add_child(top_layout.static_cast_to<gui::Widget>());
    root->add_child(top_bar.static_cast_to<gui::Widget>());

    // Left Column (Icons)
    auto left_col = region.alloc<gui::widgets::Column>();
    left_col->set_rect({20, 60, 100, 600});
    left_col->main_axis_alignment(gui::MainAxisAlignment::Start);

    left_col->add_child(region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Files).static_cast_to<gui::Widget>());
    left_col->add_child(region.alloc<gui::widgets::Text>("Source_Root").static_cast_to<gui::Widget>());

    left_col->add_child(region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Terminal).static_cast_to<gui::Widget>());
    left_col->add_child(region.alloc<gui::widgets::Text>("Quick_Term").static_cast_to<gui::Widget>());

    left_col->add_child(region.alloc<gui::widgets::Icon>(gui::widgets::IconType::Settings).static_cast_to<gui::Widget>());
    left_col->add_child(region.alloc<gui::widgets::Text>("Core_Config").static_cast_to<gui::Widget>());

    root->add_child(left_col.static_cast_to<gui::Widget>());

    // Right Dashboard
    auto right_dash = region.alloc<gui::widgets::Column>();
    right_dash->set_rect({700, 60, 300, 650});

    // Telemetry Panel
    auto tel_panel = region.alloc<gui::widgets::Panel>();
    tel_panel->set_rect({0, 0, 300, 200});
    tel_panel->set_background_color(0x22FFFFFF);
    tel_panel->add_child(region.alloc<gui::widgets::Text>("Telemetry").static_cast_to<gui::Widget>());

    auto graph = region.alloc<gui::widgets::Graph>();
    graph->set_rect({10, 40, 280, 100});
    graph->add_value(0.4f); graph->add_value(0.6f); graph->add_value(0.5f); graph->add_value(0.8f);
    tel_panel->add_child(graph.static_cast_to<gui::Widget>());

    right_dash->add_child(tel_panel.static_cast_to<gui::Widget>());

    // Storage Panel
    auto storage_panel = region.alloc<gui::widgets::Panel>();
    storage_panel->set_rect({0, 0, 300, 150});
    storage_panel->set_background_color(0x22FFFFFF);
    storage_panel->add_child(region.alloc<gui::widgets::Text>("ACOS_ROOT").static_cast_to<gui::Widget>());

    auto pb = region.alloc<gui::widgets::ProgressBar>();
    pb->set_rect({10, 60, 280, 10});
    pb->set_value(82);
    storage_panel->add_child(pb.static_cast_to<gui::Widget>());

    right_dash->add_child(storage_panel.static_cast_to<gui::Widget>());

    // Logs Panel
    auto logs_panel = region.alloc<gui::widgets::Panel>();
    logs_panel->set_rect({0, 0, 300, 250});
    logs_panel->set_background_color(0x22FFFFFF);
    logs_panel->add_child(region.alloc<gui::widgets::Text>("RECENT LOGS").static_cast_to<gui::Widget>());

    auto lv = region.alloc<gui::widgets::ListView>();
    lv->set_rect({10, 40, 280, 200});
    lv->add_item("process_exec(0.01)");
    lv->add_item("network_stack_init");
    lv->add_item("unauthorized_access_trap");
    logs_panel->add_child(lv.static_cast_to<gui::Widget>());

    right_dash->add_child(logs_panel.static_cast_to<gui::Widget>());
    root->add_child(right_dash.static_cast_to<gui::Widget>());

    // Taskbar (Bottom centered dock)
    auto taskbar = region.alloc<Taskbar>();
    // Taskbar will self-center in DesktopShell::draw or via layout?
    // Row can center it if root is a Column. Let's just set rect for now.
    taskbar->set_rect({312, 700, 400, 50});
    root->add_child(taskbar.static_cast_to<gui::Widget>());

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
