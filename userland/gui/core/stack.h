#pragma once
#include "../widget.h"

namespace acos::gui::widgets {

class Stack : public Widget {
public:
    Stack() {}

    Size layout(BoxConstraints constraints) override {
        i32 max_w = 0;
        i32 max_h = 0;

        for (auto& child : m_children) {
            if (!child || !child->is_visible()) continue;
            Size child_size = child->layout(constraints);
            if (child_size.w > max_w) max_w = child_size.w;
            if (child_size.h > max_h) max_h = child_size.h;
            child->set_position(m_rect.x, m_rect.y);
        }

        Size self_size = constraints.constrain({max_w, max_h});
        m_rect.w = self_size.w;
        m_rect.h = self_size.h;

        clear_layout_dirty();
        return self_size;
    }

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    // Internal Fluent API
    Stack& child(Ref<Widget> c) { add_child(c); return *this; }
};

} // namespace acos::gui::widgets
