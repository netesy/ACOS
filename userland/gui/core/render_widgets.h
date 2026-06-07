#pragma once
#include "render_object.h"
#include "../icon.h"
#include "layout_types.h"

namespace acos::gui::widgets {

class RenderButton : public RenderObject {
public:
    RenderButton();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_label(const char* label);
    void set_pressed(bool pressed);
    void set_hovered(bool hovered);
private:
    const char* m_label;
    bool m_pressed;
    bool m_hovered;
};

class RenderText : public RenderObject {
public:
    RenderText();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text);
    void set_alignment(::acos::gui::widgets::TextAlignment align) { m_align = align; }
private:
    const char* m_text;
    ::acos::gui::widgets::TextAlignment m_align;
};

class RenderIcon : public RenderObject {
public:
    RenderIcon();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_type(IconType type);
    void set_active(bool active);
private:
    IconType m_type;
    bool m_active;
};

class RenderCheckBox : public RenderObject {
public:
    RenderCheckBox();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_label(const char* label);
    void set_checked(bool checked);
private:
    const char* m_label;
    bool m_checked;
};

class RenderSlider : public RenderObject {
public:
    RenderSlider();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_value(float v);
    void set_range(float min, float max);
private:
    float m_value, m_min, m_max;
};

class RenderSwitch : public RenderObject {
public:
    RenderSwitch();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_label(const char* label);
    void set_on(bool on);
private:
    const char* m_label;
    bool m_on;
};

class RenderRadioButton : public RenderObject {
public:
    RenderRadioButton();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_label(const char* label);
    void set_selected(bool selected);
private:
    const char* m_label;
    bool m_selected;
};

class RenderProgressBar : public RenderObject {
public:
    RenderProgressBar();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_value(float v);
    void set_range(float min, float max);
private:
    float m_value, m_min, m_max;
};

class RenderPanel : public RenderObject {
public:
    RenderPanel();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_glass(bool glass);
private:
    bool m_is_glass;
};

class RenderStack : public RenderObject {
public:
    RenderStack();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
};

class RenderGrid : public RenderObject {
public:
    RenderGrid();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_columns(::acos::u32 columns) { m_columns = columns; }
    void set_spacing(::acos::i32 spacing) { m_spacing = spacing; }
private:
    ::acos::u32 m_columns;
    ::acos::i32 m_spacing;
};

class RenderListView : public RenderObject {
public:
    RenderListView();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_items(const char** items, ::acos::usize count);
    void set_selected(::acos::i32 index);
private:
    const char* m_items[64];
    ::acos::usize m_count;
    ::acos::i32 m_selected;
};

class RenderTextArea : public RenderObject {
public:
    RenderTextArea();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text);
private:
    char m_text[2048];
};

class RenderTextBox : public RenderObject {
public:
    RenderTextBox();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text);
    void set_placeholder(const char* placeholder);
    void set_cursor(::acos::u32 cursor, bool visible);
private:
    const char* m_text;
    const char* m_placeholder;
    ::acos::u32 m_cursor;
    bool m_cursor_visible;
};

class RenderGraph : public RenderObject {
public:
    RenderGraph();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_data(const float* data, ::acos::u32 count);
private:
    float m_data[64];
    ::acos::u32 m_count;
};

class RenderBadge : public RenderObject {
public:
    RenderBadge();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text);
private:
    const char* m_text;
};

} // namespace acos::gui::widgets
