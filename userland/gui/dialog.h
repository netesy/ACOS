#pragma once
#include "window_widget.h"
#include "button.h"

namespace acos::gui {

class Dialog : public WindowWidget {
public:
    Ref<RenderObject> create_render_object() override;
    Dialog(const char* title, i32 w, i32 h);
    virtual ~Dialog();


    void set_on_accept(void (*callback)(void*), void* receiver);
    void set_on_cancel(void (*callback)(void*), void* receiver);

protected:
    Button m_accept_btn;
    Button m_cancel_btn;
};

} // namespace acos::gui
