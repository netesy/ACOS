#pragma once
#include "widget.h"

namespace acos::gui {

class StackWidget : public Widget {
public:
    StackWidget();
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    void add_widget(Widget* widget);
    void set_current_index(u32 index);
    u32 current_index() const { return m_current_index; }

private:
    Widget* m_pages[16];
    u32 m_count;
    u32 m_current_index;
};

} // namespace acos::gui
