#pragma once
#include "widget.h"

namespace acos::gui {

enum class TextAlignment {
    Left,
    Center,
    Right
};

class Label : public Widget {
public:
    Label(const char* text = nullptr);
    virtual ~Label();

    void draw(acos::graphics::Renderer* renderer) override;
    
    void set_text(const char* text) { m_text = text; }
    void set_text_color(u32 color) { m_text_color = color; }
    void set_alignment(TextAlignment align) { m_alignment = align; }
    void set_font_size(u32 size) { m_font_size = size; }

    // Fluent API
    Label& text(const char* t) { set_text(t); return *this; }
    Label& color(u32 c) { set_text_color(c); return *this; }
    Label& font_size(u32 s) { set_font_size(s); return *this; }

    Ref<RenderObject> create_render_object() override;

protected:
    const char* m_text;
    u32 m_text_color;
    TextAlignment m_alignment;
    u32 m_font_size;
};

} // namespace acos::gui
