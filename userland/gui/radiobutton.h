#pragma once
#include "widget.h"

namespace acos::gui {

class RadioButtonGroup;

class RadioButton : public Widget {
public:
    RadioButton(const char* label = nullptr);
    virtual ~RadioButton();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    bool selected() const { return m_selected; }
    void set_selected(bool selected);

    void set_group(RadioButtonGroup* group) { m_group = group; }

private:
    const char* m_label;
    bool m_selected;
    RadioButtonGroup* m_group;
};

class RadioButtonGroup {
public:
    RadioButtonGroup();
    void add_button(RadioButton* button);
    void select(RadioButton* selected_button);

private:
    RadioButton* m_buttons[16];
    u32 m_count;
};

} // namespace acos::gui
