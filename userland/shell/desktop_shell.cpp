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
    top_bar->set_rect({0, 0, 1024, 42});

    auto top_content = Row()
        .main_axis_alignment(MainAxisAlignment::SpaceBetween)
        .cross_axis_alignment(CrossAxisAlignment::Center);
    top_content->set_rect({20, 0, 984, 42});

    auto top_left = Row().spacing(30).cross_axis_alignment(CrossAxisAlignment::Center);
    top_left->add_child(Text("ACOS_KERNEL").color(0xFFFFFFFF).font_size(16));
    top_left->add_child(Text("System").color(0xFFFFFFFF).border(0xFFFFFFFF, 1));
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
    auto tel = create_card("Telemetry", 210);
    tel->add_child(Badge("v1.0 STABLE").static_cast_to<gui::Widget>()); // Positioning might need manual layout or Stack
    auto cpu_row = Row().main_axis_alignment(MainAxisAlignment::SpaceBetween);
    cpu_row->set_rect({15, 45, 270, 20});
    cpu_row->add_child(Text("CPU CORE LOAD").color(0xFFFFFFFF).font_size(12));
    cpu_row->add_child(Text("42%").color(0xFFFFFFFF).font_size(12));
    tel->add_child(cpu_row);

    auto g = Graph();
    g->set_rect({15, 80, 270, 60});
    g->add_value(0.3f); g->add_value(0.5f); g->add_value(0.4f); g->add_value(0.7f); g->add_value(0.9f); g->add_value(0.6f); g->add_value(0.8f); g->add_value(1.0f);
    tel->add_child(g);

    auto tel_footer = Row().spacing(20);
    tel_footer->set_rect({15, 150, 270, 45});
    auto mem_box = Panel().radius(8).background(0x11FFFFFF).padding(10);
    mem_box->add_child(Column().spacing(2)
        .add_child(Text("MEMORY").color(0xFF888888).font_size(8))
        .add_child(Text("6.4 GB").color(0xFFFFFFFF).font_size(12)));
    tel_footer->add_child(mem_box);
    auto up_box = Panel().radius(8).background(0x11FFFFFF).padding(10);
    up_box->add_child(Column().spacing(2)
        .add_child(Text("UPTIME").color(0xFF888888).font_size(8))
        .add_child(Text("124h").color(0xFFFFFFFF).font_size(12)));
    tel_footer->add_child(up_box);
    tel->add_child(tel_footer);

    dashboard->add_child(tel);

    // Storage
    auto storage = create_card("ACOS_ROOT", 160);
    storage.border(0xFFBF00FF, 2); // Neon purple border
    auto s_content = Column().spacing(12);
    s_content->set_rect({15, 60, 270, 80});
    auto s_header = Row().main_axis_alignment(MainAxisAlignment::SpaceBetween);
    s_header->add_child(Text("SSD MOUNTED").color(0xFFFFFFFF).font_size(12));
    s_header->add_child(Text("82%").color(0xFFFFFFFF).font_size(12));
    s_content->add_child(s_header);
    s_content->add_child(ProgressBar().value(82).foreground(0xFFBF00FF));
    s_content->add_child(Row().main_axis_alignment(MainAxisAlignment::SpaceBetween)
        .add_child(Text("Encrypted: AES-256").color(0xFF888888).font_size(10))
        .add_child(Icon(widgets::IconType::Settings))); // Using Settings as a lock icon fallback
    storage->add_child(s_content);
    dashboard->add_child(storage);

    // Logs
    auto logs = create_card("RECENT LOGS", 240);
    auto log_list = Column().spacing(15);
    log_list->set_rect({15, 50, 270, 180});

    auto create_log_entry = [&](widgets::IconType t, const char* title, const char* sub, u32 icon_color) {
        auto r = Row().spacing(10);
        r->add_child(Icon(t).background(0).foreground(icon_color));
        r->add_child(Column().spacing(2)
            .add_child(Text(title).color(0xFFFFFFFF).font_size(12))
            .add_child(Text(sub).color(0xFF888888).font_size(8)));
        return r;
    };

    log_list->add_child(create_log_entry(widgets::IconType::Terminal, "process_exec(0.01)", "PID: 4122 | State: SLEEPING", 0xFF00E5FF));
    log_list->add_child(create_log_entry(widgets::IconType::Network, "network_stack_init", "Packet drop: 0% | Latency: 2ms", 0xFFBF00FF));
    log_list->add_child(create_log_entry(widgets::IconType::Settings, "unauthorized_access_trap", "Blocked IP: 192.168.1.104", 0xFFFF1744));

    logs->add_child(log_list);
    dashboard->add_child(logs);

    root->add_child(dashboard);

    // Taskbar (Bottom Dock)
    auto dock_container = Panel().glass(true).radius(12).background(0xCC131314);
    dock_container->set_rect({280, 710, 464, 48});

    auto taskbar = UIContext::get().region().alloc<Taskbar>();
    taskbar->set_rect({10, 0, 444, 48});
    dock_container->add_child(taskbar.static_cast_to<gui::Widget>());
    root->add_child(dock_container);

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
