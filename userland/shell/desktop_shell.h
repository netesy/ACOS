#pragma once
#include "taskbar.h"
#include "launcher.h"
#include "notification_center.h"
#include <kernel/graphics/renderer.h>

namespace acos::shell {

class DesktopShell {
public:
    DesktopShell();
    void initialize();
    void run();
    void draw(acos::graphics::Renderer* renderer);

private:
    Taskbar m_taskbar;
    Launcher m_launcher;
    NotificationCenter m_notifications;
};

} // namespace acos::shell
