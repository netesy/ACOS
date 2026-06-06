#pragma once
#include "widget.h"

namespace acos::gui {

class WindowWidget : public Widget {
public:
    WindowWidget(const char* title, ::acos::i32 x, ::acos::i32 y, ::acos::i32 w, ::acos::i32 h);
    ~WindowWidget();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void show();

private:
    [[maybe_unused]] const char* m_title;
    [[maybe_unused]] ::acos::u64 m_window_handle;
};

} // namespace acos::gui
