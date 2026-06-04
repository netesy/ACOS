#pragma once
#include "render_object.h"

namespace acos::gui {

class RenderButton : public RenderObject {
public:
    RenderButton();
    void paint(acos::graphics::Renderer* renderer) override;
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
    void paint(acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_text(const char* text);
private:
    const char* m_text;
};

class RenderCheckBox : public RenderObject {
public:
    RenderCheckBox();
    void paint(acos::graphics::Renderer* renderer) override;
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
    void paint(acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_value(float v);
    void set_range(float min, float max);
private:
    float m_value, m_min, m_max;
};

class RenderSwitch : public RenderObject {
public:
    RenderSwitch();
    void paint(acos::graphics::Renderer* renderer) override;
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
    void paint(acos::graphics::Renderer* renderer) override;
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
    void paint(acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
    void set_value(float v);
    void set_range(float min, float max);
private:
    float m_value, m_min, m_max;
};

} // namespace acos::gui
