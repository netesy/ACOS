#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/textbox.h>
#include <userland/gui/textarea.h>

namespace acos::apps {

class Terminal : public gui::WindowWidget {
public:
    Terminal();
    void on_input(const char* cmd);
    void append_output(const char* text);

private:
    gui::Ref<gui::widgets::TextBox> m_input_line;
    gui::Ref<gui::widgets::TextArea> m_output_area;
    char m_history_buffer[2048];
};

} // namespace acos::apps
