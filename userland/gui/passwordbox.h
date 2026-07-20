#pragma once
#include "textbox.h"
#include "core/render_object.h"

namespace acos::gui::widgets {

class PasswordBox : public TextBox {
public:
    PasswordBox();
    ~PasswordBox();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
};

class RenderPasswordBox : public RenderObject {
public:
    RenderPasswordBox();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text) { m_text = text; }
private:
    const char* m_text;
};

} // namespace acos::gui::widgets
