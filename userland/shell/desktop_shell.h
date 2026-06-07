#pragma once
#include <kernel/graphics/renderer.h>
#include <userland/gui/core/context.h>

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

private:
    static DesktopShell* s_instance;
    gui::UIContext m_ui_context;
    gui::Ref<gui::Widget> m_root_panel;
};

} // namespace acos::shell
