#include "terminal.h"

namespace acos::apps {

Terminal::Terminal() : gui::WindowWidget("Terminal", 50, 50, 600, 400) {
    add_child(&m_input_line);
    m_input_line.set_position(55, 370);
    m_input_line.set_size(590, 25);
}

void Terminal::on_input(const char* cmd) {
    (void)cmd;
    // Process command
}

} // namespace acos::apps
