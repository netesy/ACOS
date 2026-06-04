#pragma once
#include "widget.h"

namespace acos::gui {

class Calendar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Calendar();

private:
    [[maybe_unused]] u32 m_year;
    [[maybe_unused]] u32 m_month;
    u32 m_selected_day;
};

} // namespace acos::gui
