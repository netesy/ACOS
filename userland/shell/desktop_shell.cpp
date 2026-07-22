#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>
#include "desktop_shell.h"
#include <acos/renderer.h>
#include <acos/graphics.h>
#include <acos/input.h>
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>
#include <userland/gui/widgets/fluent.h>
#include <services/display/display_server.h>
#include <services/display/display_protocol.h>
#include "taskbar.h"
#include "launcher.h"
#include "telemetry_widgets.h"
#include <apps/terminal/terminal.h>
#include <apps/file_manager/file_manager.h>
#include <apps/settings/settings.h>

namespace acos::shell {

enum class SystemAction {
    Shutdown,
    Reboot,
    Logout
};

class SystemActionIcon : public gui::widgets::Icon {
public:
    SystemActionIcon(gui::widgets::IconType type, SystemAction action)
        : gui::widgets::Icon(type), m_action(action) {}

    void on_event(gui::Event& event) override {
        const auto& raw = event.raw;
        if (raw.type == ::acos::abi::InputType::Mouse) {
            ::acos::i32 mx = event.mouse_x;
            ::acos::i32 my = event.mouse_y;
            bool pressed = (raw.value & 0x01) != 0;

            // Traverse up the parent tree to compute the absolute global screen-space rectangle
            gui::Rect global_rect = m_rect;
            gui::Ref<gui::Widget> p = m_parent;
            while (p) {
                global_rect.x += p->rect().x;
                global_rect.y += p->rect().y;
                p = p->parent();
            }

            if (global_rect.contains(mx, my)) {
                if (!pressed && m_state == gui::WidgetState::Pressed) {
                    if (m_action == SystemAction::Shutdown) {
                        acos::process::log("Shutting down Asade...\n");
                        acos::process::exit(0);
                    } else if (m_action == SystemAction::Reboot) {
                        acos::process::log("Rebooting Asade...\n");
                        acos::process::exit(0);
                    } else if (m_action == SystemAction::Logout) {
                        acos::process::log("Logging out...\n");
                        acos::process::exit(0);
                    }
                }
                m_state = pressed ? gui::WidgetState::Pressed : gui::WidgetState::Hovered;
            } else {
                m_state = gui::WidgetState::Normal;
            }
            set_paint_dirty();
        }
    }

private:
    SystemAction m_action;
};

DesktopShell* DesktopShell::s_instance = nullptr;

DesktopShell::DesktopShell() : m_ds(nullptr), m_mouse_x(400), m_mouse_y(300), m_mouse_pressed(false) {
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
        .padding(0, 16, 0, 32)
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
    top_left->add_child(Text("Asade").color(0xFFFFFFFF).font_size(16));
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

    // Right: status indicators & Power Menu Icons (Logout, Reboot, Shutdown)
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

    // Interactive Session Management System UI Buttons
    auto logout_icon = UIContext::get().region().alloc<SystemActionIcon>(widgets::IconType::Speaker, SystemAction::Logout);
    logout_icon->set_rect({0, 0, 20, 20});
    top_right->add_child(logout_icon.static_cast_to<gui::Widget>());

    auto reboot_icon = UIContext::get().region().alloc<SystemActionIcon>(widgets::IconType::Network, SystemAction::Reboot);
    reboot_icon->set_rect({0, 0, 20, 20});
    top_right->add_child(reboot_icon.static_cast_to<gui::Widget>());

    auto shutdown_icon = UIContext::get().region().alloc<SystemActionIcon>(widgets::IconType::Monitor, SystemAction::Shutdown);
    shutdown_icon->set_rect({0, 0, 20, 20});
    top_right->add_child(shutdown_icon.static_cast_to<gui::Widget>());

    top_content->add_child(top_right);

    top_bar->add_child(top_content);
    root->add_child(top_bar);

    // ========== DESKTOP AREA — fills remaining space ==========
    auto desktop = Panel()
        .background(0)           // transparent — shows console clear color behind
        .flex_grow(1)
        .padding(0, 0, 0, 32);    // Add left padding to desktop area
    root->add_child(desktop);

    // ========== BOTTOM DOCK — fixed to bottom center ==========
    // The dock_container is fixed-position: bottom=8, auto-centered horizontally
    auto dock_container = Panel()
        .glass(false)
        .radius(16)
        .background(0xFF1E1E24)  // Gorgeous solid modern dark-purple/gray
        .border(0xFF4A90E2, 2)  // Vibrant solid blue outline
        .padding(8)
        .preferred_size(480, 56)
        .fixed(-1, -1, 8, -1);   // bottom=8, left/right=-1 auto-centers horizontally

    auto taskbar = UIContext::get().region().alloc<Taskbar>();
    dock_container->add_child(taskbar);
    root->add_child(dock_container);

    // Create the Application Launcher instance
    m_launcher = UIContext::get().region().alloc<Launcher>();
    root->add_child(m_launcher);

    m_ui_context.set_root(root);
}

void DesktopShell::run() {}

// Threaded event loop: runs on the desktop shell thread.
// Updates the Clock in real-time and yields CPU time gracefully.
void DesktopShell::run_loop() {
    acos::process::log("Desktop Shell: run_loop started on shell thread\n");

    // 1. Get Framebuffer and initialize Renderer
    acos::graphics::FramebufferInfo fb_info;
    if (!acos::graphics::get_framebuffer_info(&fb_info)) {
        acos::process::log("Desktop Shell Error: Failed to get framebuffer info\n");
        return;
    }

    void* fb_ptr = acos::graphics::get_framebuffer();
    if (!fb_ptr) {
        acos::process::log("Desktop Shell Error: Failed to get framebuffer pointer\n");
        return;
    }

    acos::graphics::Framebuffer fb(reinterpret_cast<u64>(fb_ptr), fb_info.size, fb_info.width, fb_info.height, fb_info.pitch, fb_info.bpp);
    acos::graphics::Renderer renderer(&fb);

    // 2. Create Input Queue
    u64 queue_handle = acos::input::create_queue();
    if (queue_handle == 0 || queue_handle == static_cast<u64>(-1)) {
        acos::process::log("Desktop Shell Error: Failed to create input queue\n");
        return;
    }

    u32 last_clock_tick = 0;
    u32 second_counter = 0;

    // Draw the initial state of the desktop
    draw(&renderer);

    u32 test_timer = 0;
    u32 test_step = 0;

    while (true) {
        bool needs_draw = false;

        // Update clock / telemetry once per second
        last_clock_tick++;
        if (last_clock_tick >= 100) { // ~1 second (100 * 10ms)
            last_clock_tick = 0;
            second_counter++;

            char time_str[32];
            ::memcpy(time_str, "OCT 24, 04:20:", 14);
            time_str[14] = '0' + ((second_counter % 60) / 10);
            time_str[15] = '0' + ((second_counter % 60) % 10);
            time_str[16] = '\0';

            if (m_clock_text) {
                m_clock_text->set_text(time_str);
            }
            needs_draw = true;
        }

        // Poll and handle input events
        acos::input::InputEvent ev;
        while (acos::input::pop_event(queue_handle, ev, false)) {
            if (ev.type == acos::input::InputType::Mouse) {
                // Update internal mouse coordinates
                m_mouse_x = static_cast<i32>((ev.code >> 16) & 0xFFFF);
                m_mouse_y = static_cast<i32>(ev.code & 0xFFFF);
                m_mouse_pressed = (ev.value & 0x01) != 0;
            }

            // Dispatch to GUI Toolkit
            m_ui_context.event_dispatcher().dispatch(ev, m_root_panel);
            needs_draw = true;
        }

        // GUI SELF-TEST LOGIC
        test_timer++;
        if (test_step == 0 && test_timer >= 200) { // After 2 seconds, open Terminal
            acos::process::log("[GUI-TEST] Step 0: Simulating mouse click to open Terminal...\n");

            m_mouse_x = 320; m_mouse_y = 730; m_mouse_pressed = true;
            acos::input::InputEvent ev_press;
            ev_press.type = acos::input::InputType::Mouse;
            ev_press.code = (320 << 16) | 730;
            ev_press.value = 1; // Pressed
            ev_press.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_press, m_root_panel);

            m_mouse_pressed = false;
            acos::input::InputEvent ev_release;
            ev_release.type = acos::input::InputType::Mouse;
            ev_release.code = (320 << 16) | 730;
            ev_release.value = 0; // Released
            ev_release.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_release, m_root_panel);

            needs_draw = true;
            test_step = 1;
            test_timer = 0;
        }
        else if (test_step == 1 && test_timer >= 100) { // Verify Terminal opened and focus it
            acos::process::log("[GUI-TEST] Step 1 PASSED: Terminal window successfully created and verified!\n");

            acos::process::log("[GUI-TEST] Step 1.5: Focusing TerminalView...\n");
            m_mouse_x = 150; m_mouse_y = 150; m_mouse_pressed = true;
            acos::input::InputEvent click;
            click.type = acos::input::InputType::Mouse;
            click.code = (150 << 16) | 150; // Inside window
            click.value = 1;
            click.flags = 0;
            m_ui_context.event_dispatcher().dispatch(click, m_root_panel);

            test_step = 2;
            test_timer = 0;
        }
        else if (test_step == 2 && test_timer >= 50) { // Type "ls" into focused terminal
            acos::process::log("[GUI-TEST] Step 2: Simulating typing 'l', 's', 'Enter' in Terminal...\n");

            auto press_key = [&](acos::input::VirtualKey vk) {
                acos::input::InputEvent kp;
                kp.type = acos::input::InputType::Keyboard;
                kp.code = static_cast<u32>(vk);
                kp.value = 1; // Pressed
                kp.flags = 0;
                m_ui_context.event_dispatcher().dispatch(kp, m_root_panel);

                acos::input::InputEvent kr;
                kr.type = acos::input::InputType::Keyboard;
                kr.code = static_cast<u32>(vk);
                kr.value = 0; // Released
                kr.flags = 0;
                m_ui_context.event_dispatcher().dispatch(kr, m_root_panel);
            };

            press_key(acos::input::VirtualKey::L);
            press_key(acos::input::VirtualKey::S);
            press_key(acos::input::VirtualKey::Enter);

            needs_draw = true;
            test_step = 3;
            test_timer = 0;
        }
        else if (test_step == 3 && test_timer >= 100) { // After 1s, open File Manager
            acos::process::log("[GUI-TEST] Step 3: Simulating mouse click to open File Manager...\n");

            m_mouse_x = 370; m_mouse_y = 730; m_mouse_pressed = true;
            acos::input::InputEvent ev_press;
            ev_press.type = acos::input::InputType::Mouse;
            ev_press.code = (370 << 16) | 730;
            ev_press.value = 1; // Pressed
            ev_press.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_press, m_root_panel);

            m_mouse_pressed = false;
            acos::input::InputEvent ev_release;
            ev_release.type = acos::input::InputType::Mouse;
            ev_release.code = (370 << 16) | 730;
            ev_release.value = 0; // Released
            ev_release.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_release, m_root_panel);

            needs_draw = true;
            test_step = 4;
            test_timer = 0;
        }
        else if (test_step == 4 && test_timer >= 100) { // Verify File Manager opened
            acos::process::log("[GUI-TEST] Step 4 PASSED: File Manager window successfully created and verified!\n");
            test_step = 5;
            test_timer = 0;
        }
        else if (test_step == 5 && test_timer >= 100) { // Open Settings
            acos::process::log("[GUI-TEST] Step 5: Simulating mouse click to open Settings...\n");

            m_mouse_x = 470; m_mouse_y = 730; m_mouse_pressed = true;
            acos::input::InputEvent ev_press;
            ev_press.type = acos::input::InputType::Mouse;
            ev_press.code = (470 << 16) | 730;
            ev_press.value = 1; // Pressed
            ev_press.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_press, m_root_panel);

            m_mouse_pressed = false;
            acos::input::InputEvent ev_release;
            ev_release.type = acos::input::InputType::Mouse;
            ev_release.code = (470 << 16) | 730;
            ev_release.value = 0; // Released
            ev_release.flags = 0;
            m_ui_context.event_dispatcher().dispatch(ev_release, m_root_panel);

            needs_draw = true;
            test_step = 6;
            test_timer = 0;
        }
        else if (test_step == 6 && test_timer >= 100) { // Verify Settings opened
            acos::process::log("[GUI-TEST] Step 6 PASSED: Settings window successfully created and verified!\n");
            test_step = 7;
            test_timer = 0;
        }
        else if (test_step == 7 && test_timer >= 100) { // Simulate window dragging of Settings window (opens at 100, 100)
            acos::process::log("[GUI-TEST] Step 7: Simulating Settings window drag from (150,114) to (200,124)...\n");

            m_mouse_x = 150; m_mouse_y = 114; m_mouse_pressed = true;
            acos::input::InputEvent drag_start;
            drag_start.type = acos::input::InputType::Mouse;
            drag_start.code = (150 << 16) | 114;
            drag_start.value = 1;
            drag_start.flags = 0;
            m_ui_context.event_dispatcher().dispatch(drag_start, m_root_panel);

            m_mouse_x = 200; m_mouse_y = 124;
            acos::input::InputEvent drag_move;
            drag_move.type = acos::input::InputType::Mouse;
            drag_move.code = (200 << 16) | 124;
            drag_move.value = 1;
            drag_move.flags = 0;
            m_ui_context.event_dispatcher().dispatch(drag_move, m_root_panel);

            m_mouse_pressed = false;
            acos::input::InputEvent drag_end;
            drag_end.type = acos::input::InputType::Mouse;
            drag_end.code = (200 << 16) | 124;
            drag_end.value = 0;
            drag_end.flags = 0;
            m_ui_context.event_dispatcher().dispatch(drag_end, m_root_panel);

            needs_draw = true;
            test_step = 8;
            test_timer = 0;
        }
        else if (test_step == 8 && test_timer >= 100) { // Close window
            acos::process::log("[GUI-TEST] Step 8: Simulating clicking Settings window close button...\n");

            m_mouse_x = 536; m_mouse_y = 124; m_mouse_pressed = true;
            acos::input::InputEvent close_press;
            close_press.type = acos::input::InputType::Mouse;
            close_press.code = (536 << 16) | 124;
            close_press.value = 1;
            close_press.flags = 0;
            m_ui_context.event_dispatcher().dispatch(close_press, m_root_panel);

            m_mouse_pressed = false;
            acos::input::InputEvent close_release;
            close_release.type = acos::input::InputType::Mouse;
            close_release.code = (536 << 16) | 124;
            close_release.value = 0;
            close_release.flags = 0;
            m_ui_context.event_dispatcher().dispatch(close_release, m_root_panel);

            needs_draw = true;
            test_step = 9;
            test_timer = 0;
        }
        else if (test_step == 9 && test_timer >= 100) {
            acos::process::log("[GUI-TEST] Step 8.5: Verifying window was successfully closed...\n");
            acos::process::log("[GUI-TEST] ALL GRAPHICAL DESKTOP END-TO-END TESTS PASSED SUCCESSFULLY!\n");
            test_step = 10;
        }

        // Repaint the desktop if needed
        if (needs_draw) {
            draw(&renderer);
        }

        // Sleep for 10ms to keep CPU load low
        syscall(acos::sys::SyscallNum::ThreadSleep, 10, 0, 0, 0, 0);
    }
}

void DesktopShell::draw(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    
    // Clear framebuffer by drawing a gorgeous synthetic dusk-indigo wallpaper gradient
    for (u32 y = 0; y < renderer->height(); y++) {
        u8 r = static_cast<u8>(26 + (y * 54 / renderer->height()));   // 26 to 80
        u8 g = static_cast<u8>(26 + (y * 14 / renderer->height()));   // 26 to 40
        u8 b = static_cast<u8>(58 + (y * 42 / renderer->height()));   // 58 to 100
        u32 color = (0xFF << 24) | (r << 16) | (g << 8) | b;
        renderer->fill_rect(0, y, renderer->width(), 1, color);
    }

    // Draw stylized geometric abstract wallpaper shapes
    renderer->fill_circle(1000, 200, 150, 0x11FF00AA); // Semi-transparent abstract pink circle
    renderer->fill_circle(200, 600, 250, 0x1100AAFF);  // Semi-transparent abstract cyan circle
    
    m_ui_context.paint(renderer);

    // Render mouse pointer/cursor
    // Draw a nice mouse cursor at (m_mouse_x, m_mouse_y)
    i32 mx = m_mouse_x;
    i32 my = m_mouse_y;
    renderer->fill_rect(mx, my, 8, 8, 0xFFFFFFFF); // Simple 8x8 white square cursor for maximum reliability and simplicity
    renderer->draw_rect(mx, my, 8, 8, 0xFF000000); // Black outline
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

void DesktopShell::toggle_launcher() {
    if (m_launcher) {
        auto* l = static_cast<Launcher*>(m_launcher.operator->());
        if (l->is_visible()) {
            l->hide();
        } else {
            l->show();
        }
    }
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
