#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class GroupBox : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    GroupBox(const char* title = nullptr);
    virtual ~GroupBox();

private:
    [[maybe_unused]] const char* m_title;
};

} // namespace acos::gui::widgets
