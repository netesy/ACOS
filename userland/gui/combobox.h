#pragma once
#include "widget.h"
#include "listview.h"

namespace acos::gui {

class ComboBox : public Widget {
public:
    ComboBox();
    virtual ~ComboBox();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    void add_item(const char* item);
    const char* selected_item() const;

private:
    ListView m_popup;
    bool m_expanded;
    const char* m_current_text;
};

} // namespace acos::gui
