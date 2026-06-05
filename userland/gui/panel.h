#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Panel : public Widget {
public:
    Panel();
    virtual ~Panel();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void set_background_color(u32 color) { m_bg_color = color; set_paint_dirty(); }
    void set_glass(bool glass) { m_is_glass = glass; set_paint_dirty(); }

    // Internal Fluent API
    Panel& color(u32 c) { set_background_color(c); return *this; }
    Panel& glass(bool g) { set_glass(g); return *this; }
    Panel& child(Ref<Widget> c) { add_child(c); return *this; }

private:
    u32 m_bg_color;
    bool m_is_glass;
};

} // namespace acos::gui::widgets
