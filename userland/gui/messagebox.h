#pragma once
#include "window_widget.h"
#include "button.h"
#include "label.h"

namespace acos::gui {

class MessageBox : public WindowWidget {
public:
    MessageBox(const char* title, const char* message);
    virtual ~MessageBox();

    void draw(acos::graphics::Renderer* renderer) override;

private:
    Label m_label;
    Button m_ok_btn;
};

} // namespace acos::gui
