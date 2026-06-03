#pragma once
#include <ui/window_widget.h>
#include <ui/textbox.h>

namespace acos::apps {

class Terminal : public ui::WindowWidget {
public:
    Terminal();
    void on_input(const char* cmd);

private:
    ui::TextBox m_input_line;
};

} // namespace acos::apps
