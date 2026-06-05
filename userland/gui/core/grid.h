#pragma once
#include "../widget.h"

namespace acos::gui::widgets {

class Grid : public Widget {
public:
    Grid(u32 columns, i32 spacing = 0) : m_columns(columns), m_spacing(spacing) {}

    Size layout(BoxConstraints constraints) override {
        if (m_columns == 0) return constraints.constrain({0, 0});

        u32 visible_count = 0;
        for (auto& child : m_children) if (child && child->is_visible()) visible_count++;

        if (visible_count == 0) return constraints.constrain({0, 0});

        u32 rows = (visible_count + m_columns - 1) / m_columns;
        i32 cell_w = (constraints.max_w - (m_columns - 1) * m_spacing) / m_columns;

        // This grid assumes uniform cell width, but allows children to determine height
        // for each row based on the tallest child in that row.
        // For simplicity, let's start with uniform cell size.
        i32 cell_h = (constraints.max_h - (rows - 1) * m_spacing) / rows;

        BoxConstraints cell_constraints = BoxConstraints::tight(cell_w, cell_h);

        u32 i = 0;
        for (auto& child : m_children) {
            if (!child || !child->is_visible()) continue;

            u32 r = i / m_columns;
            u32 c = i % m_columns;

            child->layout(cell_constraints);
            child->set_position(m_rect.x + c * (cell_w + m_spacing), m_rect.y + r * (cell_h + m_spacing));
            i++;
        }

        Size self_size = constraints.constrain({constraints.max_w, constraints.max_h});
        m_rect.w = self_size.w;
        m_rect.h = self_size.h;

        clear_layout_dirty();
        return self_size;
    }

    Ref<RenderObject> create_render_object() override;

    // Internal Fluent API
    Grid& child(Ref<Widget> c) { add_child(c); return *this; }

private:
    u32 m_columns;
    i32 m_spacing;
};

} // namespace acos::gui::widgets
