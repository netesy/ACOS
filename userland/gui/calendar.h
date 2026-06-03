#pragma once
#include "widget.h"

namespace acos::gui {

class Calendar : public Widget {
public:
    Calendar();
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

private:
    [[maybe_unused]] u32 m_year;
    [[maybe_unused]] u32 m_month;
    u32 m_selected_day;
};

} // namespace acos::gui
