#pragma once
#include "widget.h"

namespace acos::gui::widgets {

enum class TextAlignment {
    Left,
    Center,
    Right
};

class Text : public Widget {
public:
    Text(const char* text = nullptr);
    virtual ~Text();
    
    void set_text(const char* text) { m_text = text; }
    void set_text_color(u32 color) { m_text_color = color; }
    void set_alignment(TextAlignment align) { m_alignment = align; }
    void set_font_size(u32 size) { m_font_size = size; }

    // Internal Fluent API
    Text& text(const char* t) { set_text(t); return *this; }
    Text& color(u32 c) { set_text_color(c); return *this; }
    Text& font_size(u32 s) { set_font_size(s); return *this; }

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

protected:
    const char* m_text;
    u32 m_text_color;
    TextAlignment m_alignment;
    u32 m_font_size;
};

} // namespace acos::gui
