#pragma once
#include <kernel/graphics/renderer.h>
#include <userland/gui/core/context.h>
#include <userland/gui/text.h>
#include "shortcut_manager.h"

namespace acos::shell {

class DesktopShell {
public:
    DesktopShell();
    void initialize();
    void run();
    void draw(acos::graphics::Renderer* renderer);

    static DesktopShell& get() { return *s_instance; }
    void launch_terminal();
    void launch_file_manager();
    void launch_settings();

    void update_status_bar();
    void toggle_search();

    DesktopShortcutManager& shortcut_manager() { return m_shortcut_manager; }

private:
    static DesktopShell* s_instance;
    gui::UIContext m_ui_context;
    gui::Ref<gui::Widget> m_root_panel;
    gui::Ref<gui::widgets::Text> m_ip_text;
    gui::Ref<gui::widgets::Text> m_clock_text;
    gui::Ref<gui::Widget> m_search_modal;
    DesktopShortcutManager m_shortcut_manager;
};

} // namespace acos::shell
