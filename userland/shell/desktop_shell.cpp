#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include <userland/gui/widgets/fluent.h>
#include "taskbar.h"
#include "launcher.h"
#include <apps/terminal/terminal.h>
#include <apps/file_manager/file_manager.h>
#include <apps/settings/settings.h>

namespace acos::shell {

DesktopShell* DesktopShell::s_instance = nullptr;

DesktopShell::DesktopShell() {
    s_instance = this;
    gui::widgets::init_synthetic_theme();
}

void DesktopShell::initialize() {
    using namespace gui;

    auto root = Panel()
        .background(0xFF0A0A0B);
    root->set_rect({0, 0, 1024, 768});
    m_root_panel = root.static_cast_to<gui::Widget>();

    // Top Bar
    auto top_bar = Panel()
        .glass(true)
        .background(0xCC0A0A0B); // More opaque dark glass
    top_bar->set_rect({0, 0, 1024, 48});

    auto top_content = Row()
        .main_axis_alignment(MainAxisAlignment::SpaceBetween)
        .cross_axis_alignment(CrossAxisAlignment::Center);
    top_content->set_rect({20, 0, 984, 48});

    auto top_left = Row().spacing(25).cross_axis_alignment(CrossAxisAlignment::Center);
    top_left->add_child(Text("ACOS_KERNEL").color(0xFFFFFFFF).font_size(16));
    top_left->add_child(Text("System").color(widgets::g_current_theme.accent));
    top_left->add_child(Text("Network").color(0xFF888888));
    top_left->add_child(Text("Security").color(0xFF888888));
    top_content->add_child(top_left);

    // Search Box
    auto search = Panel().radius(20).background(0x22FFFFFF);
    search->set_rect({0, 0, 240, 28});
    search->add_child(Text("  Search (Ctrl+Space)").color(0xFF888888).font_size(12));
    top_content->add_child(search);

    auto top_right = Row().spacing(15).main_axis_alignment(MainAxisAlignment::End);
    top_right->add_child(Text("127.0.0.1").color(0xFF888888));
    top_right->add_child(Text("OCT 24, 04:20:01").color(0xFFFFFFFF));
    top_right->add_child(Icon(widgets::IconType::Settings));
    top_right->add_child(Icon(widgets::IconType::Battery));

    top_content->add_child(top_right);
    top_bar->add_child(top_content);
    root->add_child(top_bar);

    // Sidebar
    auto sidebar = Column().spacing(30);
    sidebar->set_rect({20, 80, 80, 600});

    auto create_nav_icon = [&](widgets::IconType t, const char* label, void (*callback)(void*)) {
        auto c = Column().spacing(5).cross_axis_alignment(CrossAxisAlignment::Center);
        c->add_child(Icon(t).background(0x22FFFFFF).radius(8).on_click(callback));
        c->add_child(Text(label).color(0xFF888888).font_size(10));
        return c;
    };

    sidebar->add_child(create_nav_icon(widgets::IconType::Files, "Source_Root", [](void*){ DesktopShell::get().launch_file_manager(); }));
    sidebar->add_child(create_nav_icon(widgets::IconType::Terminal, "Quick_Term", [](void*){ DesktopShell::get().launch_terminal(); }));
    sidebar->add_child(create_nav_icon(widgets::IconType::Settings, "Core_Config", [](void*){ DesktopShell::get().launch_settings(); }));

    root->add_child(sidebar);

    // Dashboard (Right)
    auto dashboard = Column().spacing(20);
    dashboard->set_rect({712, 80, 300, 600});

    auto create_card = [&](const char* title, i32 h) {
        auto p = Panel().glass(true).radius(12).padding(15).background(0xCC1A1A1B);
        p->set_rect({0, 0, 300, h});
        p->add_child(Text(title).color(0xFFFFFFFF).font_size(14));
        return p;
    };

    // Telemetry
    auto tel = create_card("Telemetry", 200);
    auto g = Graph();
    g->set_rect({15, 60, 270, 80});
    g->add_value(0.3f); g->add_value(0.5f); g->add_value(0.4f); g->add_value(0.7f); g->add_value(0.9f); g->add_value(0.6f); g->add_value(0.8f); g->add_value(0.4f);
    tel->add_child(g);
    dashboard->add_child(tel);

    // Storage
    auto storage = create_card("ACOS_ROOT", 160);
    auto s_content = Column().spacing(12);
    s_content->set_rect({15, 60, 270, 80});
    s_content->add_child(Text("SSD MOUNTED  82%").color(0xFF888888).font_size(12));
    s_content->add_child(ProgressBar().value(82));
    s_content->add_child(Text("Encrypted: AES-256").color(0xFF888888).font_size(10));
    storage->add_child(s_content);
    dashboard->add_child(storage);

    // Logs
    auto logs = create_card("RECENT LOGS", 220);
    auto lv = ListView();
    lv->set_rect({10, 40, 280, 160});
    lv->add_item("process_exec(0.01)");
    lv->add_item("network_stack_init");
    lv->add_item("unauthorized_access_trap");
    logs->add_child(lv);
    dashboard->add_child(logs);

    root->add_child(dashboard);

    // Taskbar (Bottom Dock)
    auto taskbar = UIContext::get().region().alloc<Taskbar>();
    taskbar->set_rect({312, 700, 400, 52});
    root->add_child(taskbar.static_cast_to<gui::Widget>());

    m_ui_context.set_root(root.static_cast_to<gui::Widget>());
}

void DesktopShell::run() {}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    m_ui_context.paint(renderer);
}

void DesktopShell::launch_terminal() {
    auto term = m_ui_context.region().alloc<apps::Terminal>();
    m_root_panel->add_child(term.static_cast_to<gui::Widget>());
}

void DesktopShell::launch_file_manager() {
    auto fm = m_ui_context.region().alloc<apps::FileManager>();
    m_root_panel->add_child(fm.static_cast_to<gui::Widget>());
}

void DesktopShell::launch_settings() {
    auto settings = m_ui_context.region().alloc<apps::Settings>();
    m_root_panel->add_child(settings.static_cast_to<gui::Widget>());
}

} // namespace acos::shell
