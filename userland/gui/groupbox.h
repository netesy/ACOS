#pragma once
#include "widget.h"

namespace acos::gui {

class GroupBox : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    GroupBox(const char* title = nullptr);

private:
    const char* m_title;
};

} // namespace acos::gui
