#include "desktop_shell.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include <userland/gui/widgets/fluent.h>
#include <services/display/display_server.h>
#include <services/display/display_protocol.h>
#include <kernel/hal/serial.h>
#include "taskbar.h"
#include "launcher.h"
#include "telemetry_widgets.h"
#include <apps/terminal/terminal.h>
#include <apps/file_manager/file_manager.h>
#include <apps/settings/settings.h>

namespace acos::shell {

DesktopShell* DesktopShell::s_instance = nullptr;

DesktopShell::DesktopShell() : m_ds(nullptr) {
    s_instance = this;
    gui::widgets::init_synthetic_theme();
}

void DesktopShell::initialize() {
    using namespace gui;

    // ROOT: Full-screen stack — normal flow children + fixed-position overlays
    auto root = Column().spacing(0);
    m_root_panel = root;

    // ========== TOP BAR — fixed to top, full width, 48px ==========
    auto top_bar = Panel()
        .glass(true)
        .background(0xCC0A0A0B)
        .padding(0, 16, 0, 16)
        .preferred_height(48)
        .fixed(0, 0, -1, 0);      // top=0, right=0, bottom=unset, left=0

    auto top_content = Row()
        .main_axis_alignment(MainAxisAlignment::SpaceBetween)
        .cross_axis_alignment(CrossAxisAlignment::Center)
        .spacing(20);

    // Left: brand + menu items
    auto top_left = Row()
        .spacing(24)
        .cross_axis_alignment(CrossAxisAlignment::Center);
    top_left->add_child(Text("ACOS_KERNEL").color(0xFFFFFFFF).font_size(16));
    top_left->add_child(Text("System").color(0xFFFFFFFF).border(0xFFFFFFFF, 1));
    top_left->add_child(Text("Network").color(0xFF888888));
    top_left->add_child(Text("Security").color(0xFF888888));
    top_content->add_child(top_left);

    // Center: search
    auto search = Panel()
        .radius(20)
        .background(0x22FFFFFF)
        .padding(4, 12, 4, 12)
        .preferred_size(280, 28);
    search->add_child(Text("Search (Ctrl+Space)").color(0xFF888888).font_size(12));
    top_content->add_child(search);

    // Right: status indicators
    auto top_right = Row()
        .spacing(12)
        .main_axis_alignment(MainAxisAlignment::End)
        .cross_axis_alignment(CrossAxisAlignment::Center);
    m_ip_text   = Text("127.0.0.1").color(0xFF888888);
    m_clock_text = Text("OCT 24, 04:20:01").color(0xFFFFFFFF);
    top_right->add_child(m_ip_text);
    top_right->add_child(m_clock_text);
    top_right->add_child(Icon(widgets::IconType::Settings).preferred_size(20, 20));
    top_right->add_child(Icon(widgets::IconType::Battery).preferred_size(20, 20));
    top_content->add_child(top_right);

    top_bar->add_child(top_content);
    root->add_child(top_bar);

    // ========== DESKTOP AREA — fills remaining space ==========
    auto desktop = Panel()
        .background(0)           // transparent — shows console clear color behind
        .flex_grow(1);
    root->add_child(desktop);

    // ========== BOTTOM DOCK — fixed to bottom center ==========
    // The dock_container is fixed-position: bottom=8, auto-centered horizontally
    auto dock_container = Panel()
        .glass(true)
        .radius(12)
        .background(0xCC131314)
        .padding(8)
        .preferred_size(480, 56)
        .fixed(-1, -1, 8, -1);   // bottom=8, left/right=-1 auto-centers horizontally

    auto taskbar = UIContext::get().region().alloc<Taskbar>();
    dock_container->add_child(taskbar);
    root->add_child(dock_container);

    m_ui_context.set_root(root);
}

void DesktopShell::run() {}

// Threaded event loop: runs on the desktop shell thread.
// Currently minimal — future work:
//   - Process mouse/keyboard input events
//   - Update clock/status bar periodically
//   - Handle application launch requests
void DesktopShell::run_loop() {
    acos::hal::serial_print("Desktop Shell: run_loop started on shell thread\n");

    while (true) {
        // Send damage notification to keep compositor active
        // (the desktop background is always-dirty for now)
        if (m_ds) {
            acos::display::DisplayMsg cmd{};
            cmd.type = acos::display::DisplayMsgType::DamageNotify;
            m_ds->send_command(cmd);
        }

        // Yield CPU — will be replaced by event-driven blocking
        // when input routing is implemented
        __asm__ volatile("hlt");
    }
}

void DesktopShell::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    
    // Clear framebuffer to remove any kernel console output
    renderer->fill_rect(0, 0, renderer->width(), renderer->height(), 0xFF1A1A1A);
    
    m_ui_context.paint(renderer);
}

void DesktopShell::launch_terminal() {
    auto term = m_ui_context.region().alloc<apps::Terminal>();
    m_root_panel->add_child(term);
}

void DesktopShell::launch_file_manager() {
    auto fm = m_ui_context.region().alloc<apps::FileManager>();
    m_root_panel->add_child(fm);
}

void DesktopShell::launch_settings() {
    auto settings = m_ui_context.region().alloc<apps::Settings>();
    m_root_panel->add_child(settings);
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
        
        auto input = m_ui_context.region().alloc<gui::widgets::TextBox>();
        input->set_rect({10, 10, 480, 40});
        input->set_placeholder("Search applications, files, and commands...");
        modal->add_child(input);
        
        m_search_modal = modal;
        m_root_panel->add_child(m_search_modal);
    }

    m_search_modal->set_visible(true);
    gui::UIContext::get().focus_manager().set_focus(m_search_modal);
}

} // namespace acos::shell
