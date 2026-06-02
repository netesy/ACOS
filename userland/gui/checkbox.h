#pragma once
#include "widget.h"

namespace acos::gui {

class CheckBox : public Widget {
public:
    CheckBox(const char* label = nullptr);
    virtual ~CheckBox();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    bool checked() const { return m_checked; }
    void set_checked(bool checked) { m_checked = checked; }

private:
    const char* m_label;
    bool m_checked;
};

} // namespace acos::gui
