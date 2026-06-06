#pragma once
#include "widget.h"

namespace acos::gui::widgets {

struct TreeItem {
    const char* label;
    bool expanded;
    TreeItem* children[8];
    ::acos::u32 child_count;
};

class TreeView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    TreeView();
    virtual ~TreeView();
    void add_root_item(const char* label);

private:
    TreeItem m_roots[16];
    ::acos::u32 m_root_count;
};

} // namespace acos::gui::widgets
