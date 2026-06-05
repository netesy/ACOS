#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/panel.h>

namespace acos::shell {

class Launcher : public gui::widgets::Panel {
public:
    Launcher();
    void show();
    void hide();

    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;

private:
    bool m_active;
};

} // namespace acos::shell
