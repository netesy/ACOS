#pragma once
#include "taskbar.h"
#include "launcher.h"
#include "notification_center.h"

namespace acos::shell {

class DesktopShell {
public:
    DesktopShell();
    void initialize();
    void run();

private:
    Taskbar m_taskbar;
    Launcher m_launcher;
    NotificationCenter m_notifications;

    u32* m_wallpaper_buffer;
};

} // namespace acos::shell
