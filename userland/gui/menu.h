#pragma once
#include "widget.h"
#include "listview.h"

namespace acos::gui {

class Menu : public Widget {
public:
    Menu();
    virtual ~Menu();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    void add_item(const char* label);

private:
    ListView m_list;
};

} // namespace acos::gui
