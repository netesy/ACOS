#pragma once
#include "widget.h"
#include <services/display/window.h>

namespace acos::gui {

class WindowWidget : public Widget {
public:
    WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h);
    ~WindowWidget();

    void draw(u32* buffer, u32 pitch) override;
    void add_child(Widget* child);

    void show();

private:
    const char* m_title;
    Widget* m_children[32];
    usize m_child_count;
    u64 m_window_handle;
};

} // namespace acos::gui
