#pragma once
#include "widget.h"

namespace acos::gui::widgets {

struct TreeItem {
    const char* label;
    bool expanded;
    TreeItem* children[8];
    u32 child_count;
};

class TreeView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    TreeView();
    void add_root_item(const char* label);

private:
    TreeItem m_roots[16];
    u32 m_root_count;

    void draw_item(acos::graphics::Renderer* renderer, TreeItem* item, i32& y, i32 indent);
};

} // namespace acos::gui::widgets
