#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Calendar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Calendar();
    virtual ~Calendar();

private:
    [[maybe_unused]] u32 m_year;
    [[maybe_unused]] u32 m_month;
    [[maybe_unused]] u32 m_selected_day;
};

} // namespace acos::gui::widgets
