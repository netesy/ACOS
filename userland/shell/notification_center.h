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
    void draw(u32* buffer, u32 pitch) override;
    void post_notification(const char* title, const char* message);

private:
    Notification m_queue[16];
    usize m_count;
};

} // namespace acos::shell
