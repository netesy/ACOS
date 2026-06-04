#include "window_manager.h"

namespace acos::ui {

WindowManager::WindowManager() : m_window_count(0), m_active_window(nullptr) {}

void WindowManager::add_window(Window* window) {
    if (m_window_count < 64) { m_windows[m_window_count++] = window; m_active_window = window; }
}

void WindowManager::remove_window(Window* window) {
    for (u32 i = 0; i < m_window_count; i++) {
        if (m_windows[i] == window) {
            for (u32 j = i; j < m_window_count - 1; j++) m_windows[j] = m_windows[j + 1];
            m_window_count--;
            if (m_active_window == window) m_active_window = m_window_count > 0 ? m_windows[m_window_count-1] : nullptr;
            break;
        }
    }
}

void WindowManager::update(u64 now) { for (u32 i = 0; i < m_window_count; i++) m_windows[i]->update(now); }
void WindowManager::paint(acos::graphics::Renderer* renderer) { for (u32 i = 0; i < m_window_count; i++) m_windows[i]->paint(renderer); }

void WindowManager::handle_event(UIEvent& event) {
    for (i32 i = m_window_count - 1; i >= 0; i--) {
        Window* win = m_windows[i];
        if (event.type == EventType::MouseDown || event.type == EventType::MouseMove || event.type == EventType::MouseUp) {
            if (event.mouse.x >= win->x() && event.mouse.x < win->x() + win->w() &&
                event.mouse.y >= win->y() && event.mouse.y < win->y() + win->h()) {
                win->handle_event(event);
                if (event.handled) { if (event.type == EventType::MouseDown) bring_to_front(win); return; }
            }
        } else { if (m_active_window) m_active_window->handle_event(event); return; }
    }
}

void WindowManager::bring_to_front(Window* window) {
    for (u32 i = 0; i < m_window_count; i++) {
        if (m_windows[i] == window) {
            for (u32 j = i; j < m_window_count - 1; j++) m_windows[j] = m_windows[j+1];
            m_windows[m_window_count-1] = window; m_active_window = window; break;
        }
    }
}

} // namespace acos::ui
