#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui {

class Separator : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Separator(Orientation orient = Orientation::Horizontal);

private:
    Orientation m_orientation;
};

} // namespace acos::gui
