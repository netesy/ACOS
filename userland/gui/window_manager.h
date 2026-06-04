#pragma once
#include "window.h"

namespace acos::ui {

class WindowManager {
public:
    static WindowManager& instance() { static WindowManager i; return i; }
    void add_window(Window* window);
    void remove_window(Window* window);
    void update(u64 now);
    void paint(acos::graphics::Renderer* renderer);
    void handle_event(UIEvent& event);
    void bring_to_front(Window* window);
    Window* active_window() const { return m_active_window; }
private:
    WindowManager();
    Window* m_windows[64]; u32 m_window_count; Window* m_active_window;
};

} // namespace acos::ui
