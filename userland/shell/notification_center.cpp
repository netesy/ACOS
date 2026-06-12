#include <acos/process.h>
#include <acos/runtime.h>
#include "notification_center.h"
#include <userland/gui/theme.h>
#include <userland/gui/text.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

NotificationCenter::NotificationCenter() {
    m_rect = {590, 50, 200, 400};
    set_visible(false);
    set_glass(true);

    auto& region = gui::UIContext::get().region();
    auto title = region.alloc<gui::widgets::Text>("Notifications");
    add_child(title);
}

void NotificationCenter::post_notification(const char* title, const char* message) {
    (void)title; (void)message;
}

gui::Ref<gui::RenderObject> NotificationCenter::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void NotificationCenter::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
