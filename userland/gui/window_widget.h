#pragma once
#include "widget.h"
#include <services/display/window.h>

namespace acos::gui {

class WindowWidget : public Widget {
public:
    WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h);
    ~WindowWidget();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void show();

private:
    const char* m_title;
    [[maybe_unused]] u64 m_window_handle;
};

} // namespace acos::gui
