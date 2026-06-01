#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

struct Notification {
    const char* title;
    const char* message;
    u32 priority;
};

class NotificationCenter : public gui::Widget {
public:
    NotificationCenter();
    void draw(acos::graphics::Renderer* renderer) override;
    void post_notification(const char* title, const char* message);

private:
    Notification m_queue[16];
    usize m_count;
};

} // namespace acos::shell
