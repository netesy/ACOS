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

private:
    gui::UIContext m_ui_context;
};

} // namespace acos::shell
