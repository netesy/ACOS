#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/panel.h>

namespace acos::shell {

class NotificationCenter : public gui::widgets::Panel {
public:
    NotificationCenter();
    void post_notification(const char* title, const char* message);

    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;
};

} // namespace acos::shell
