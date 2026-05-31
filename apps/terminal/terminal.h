#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/textbox.h>

namespace acos::apps {

class Terminal : public gui::WindowWidget {
public:
    Terminal();
    void on_input(const char* cmd);

private:
    gui::TextBox m_input_line;
};

} // namespace acos::apps
