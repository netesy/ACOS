#pragma once
#include "window_widget.h"
#include "button.h"
#include "label.h"

namespace acos::gui {

class MessageBox : public WindowWidget {
public:
    Ref<RenderObject> create_render_object() override;
    MessageBox(const char* title, const char* message);
    virtual ~MessageBox();


private:
    Label m_label;
    Button m_ok_btn;
};

} // namespace acos::gui
