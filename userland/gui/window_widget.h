#pragma once
#include "widget.h"
#include <services/display/window.h>

namespace acos::gui {

class WindowWidget : public Widget {
public:
    WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h);
    ~WindowWidget();

    // Implement base class draw method
    void draw(acos::graphics::Renderer* renderer) override;
    
    // Additional draw method for direct buffer rendering
    void draw_to_buffer(u32* buffer, u32 pitch);
    
    void add_child(Widget* child);

    void show();

private:
    const char* m_title;
    Widget* m_children[32];
    usize m_child_count;
    [[maybe_unused]] u64 m_window_handle;
};

} // namespace acos::gui
