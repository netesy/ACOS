#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui {

class ScrollView : public Widget {
public:
    ScrollView();
    virtual ~ScrollView();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    void add_content(Widget* widget);

private:
    ScrollBar m_v_scroll;
    Widget* m_content;
};

} // namespace acos::gui
