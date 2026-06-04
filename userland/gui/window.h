#pragma once
#include "context.h"
#include "widget.h"

namespace acos::ui {

class Window {
public:
    Window(const char* title, i32 x, i32 y, i32 w, i32 h);
    void set_root(Ref<Widget> root);
    void update(u64 now);
    void paint(acos::graphics::Renderer* renderer);
    void handle_event(UIEvent& event);
    i32 x() const { return m_x; } i32 y() const { return m_y; }
    i32 w() const { return m_w; } i32 h() const { return m_h; }
    const char* title() const { return m_title; }
private:
    const char* m_title; i32 m_x, m_y, m_w, m_h;
    UIContext m_context; Ref<Widget> m_root;
};

} // namespace acos::ui
