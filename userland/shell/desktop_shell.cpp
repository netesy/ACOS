#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include <userland/gui/widgets/fluent.h>
#include "taskbar.h"
#include "launcher.h"
#include "telemetry_widgets.h"
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
    m_ip_text = Text("127.0.0.1").color(0xFF888888);
    m_clock_text = Text("OCT 24, 04:20:01").color(0xFFFFFFFF);
    top_right->add_child(m_ip_text.static_cast_to<gui::Widget>());
    top_right->add_child(m_clock_text.static_cast_to<gui::Widget>());
    top_right->add_child(Icon(widgets::IconType::Settings));
    top_right->add_child(Icon(widgets::IconType::Battery));

    top_content->add_child(top_right);
    top_bar->add_child(top_content);
    root->add_child(top_bar);

    // Desktop Grid for Shortcuts
    auto desktop_grid = m_ui_context.region().alloc<gui::widgets::Grid>(6, 20);
    desktop_grid->set_rect({120, 80, 570, 600});
    root->add_child(desktop_grid.static_cast_to<gui::Widget>());
    m_shortcut_manager.set_grid(desktop_grid);
    m_shortcut_manager.sync();

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

    // Telemetry
    auto cpu_widget = m_ui_context.region().alloc<CPULoadWidget>();
    cpu_widget->set_rect({0, 0, 300, 210});
    cpu_widget->set_background_color(0xCC1A1A1B);
    cpu_widget->radius(12);
    cpu_widget->set_glass(true);
    dashboard->add_child(cpu_widget.static_cast_to<gui::Widget>());

    // Storage
    auto storage_widget = m_ui_context.region().alloc<StorageCardWidget>();
    storage_widget->set_rect({0, 0, 300, 160});
    storage_widget->set_background_color(0xCC1A1A1B);
    storage_widget->radius(12);
    storage_widget->set_glass(true);
    storage_widget->set_border_color(0xFFBF00FF);
    storage_widget->set_border_width(2);
    dashboard->add_child(storage_widget.static_cast_to<gui::Widget>());

    // Logs
    auto logs_widget = m_ui_context.region().alloc<RecentLogsWidget>();
    logs_widget->set_rect({0, 0, 300, 240});
    logs_widget->set_background_color(0xCC1A1A1B);
    logs_widget->radius(12);
    logs_widget->set_glass(true);
    dashboard->add_child(logs_widget.static_cast_to<gui::Widget>());

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

void DesktopShell::run() {
    // Start status bar update cycle if needed or handle async tasks
}

void DesktopShell::update(u64 delta_ms) {
    m_ui_context.update(delta_ms);
    update_status_bar();
}

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

void DesktopShell::update_status_bar() {
    // Dynamic IP (Simulated/Placeholder)
    if (m_ip_text) m_ip_text->set_text("192.168.1.105");

    // Dynamic Clock (Simulated/Placeholder)
    if (m_clock_text) m_clock_text->set_text("OCT 24, 04:20:42");
}

void DesktopShell::toggle_search() {
    if (m_search_modal && m_search_modal->is_visible()) {
        m_search_modal->set_visible(false);
        return;
    }

    if (!m_search_modal) {
        using namespace gui;
        auto modal = Panel()
            .background(0xDD0A0A0B)
            .radius(16)
            .border(0xFF4A4A4B, 1);
        modal->set_rect({262, 100, 500, 60});

        auto input = m_ui_context.region().alloc<widgets::TextBox>();
        input->set_rect({10, 10, 480, 40});
        input->set_placeholder("Search applications, files, and commands...");
        modal->add_child(input.static_cast_to<Widget>());

        m_search_modal = modal.static_cast_to<Widget>();
        m_root_panel->add_child(m_search_modal);
    }

    m_search_modal->set_visible(true);
    gui::UIContext::get().focus_manager().set_focus(m_search_modal);
}

} // namespace acos::shell
