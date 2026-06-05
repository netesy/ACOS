#include "terminal.h"
#include <userland/gui/core/context.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::apps {

Terminal::Terminal() : gui::WindowWidget("Terminal", 50, 50, 600, 400) {
    auto& region = gui::UIContext::get().region();

    m_output_area = region.alloc<gui::widgets::TextArea>();
    m_output_area->set_rect({10, 40, 580, 320});
    m_output_area->set_text("ACOS Terminal v1.0\nType 'help' for commands.\n\n$ ");
    add_child(m_output_area.static_cast_to<gui::Widget>());

    m_input_line = region.alloc<gui::widgets::TextBox>();
    m_input_line->set_position(10, 370);
    m_input_line->set_size(580, 24);
    m_input_line->set_placeholder("Enter command...");
    add_child(m_input_line.static_cast_to<gui::Widget>());

    m_history_buffer[0] = '\0';
}

void Terminal::append_output(const char* text) {
    if (!text) return;
    // Simple append logic for the history buffer
    usize cur_len = 0;
    while (m_history_buffer[cur_len]) cur_len++;

    usize i = 0;
    while (text[i] && (cur_len + i < 2047)) {
        m_history_buffer[cur_len + i] = text[i];
        i++;
    }
    m_history_buffer[cur_len + i] = '\0';
    m_output_area->set_text(m_history_buffer);
}

void Terminal::on_input(const char* cmd) {
    if (!cmd || !cmd[0]) return;

    append_output(cmd);
    append_output("\n");

    if (strcmp_impl(cmd, "help") == 0) {
        append_output("Available commands: help, ls, clear, about, exit\n");
    } else if (strcmp_impl(cmd, "about") == 0) {
        append_output("ACOS Operating System - Built for high performance.\n");
    } else if (strcmp_impl(cmd, "clear") == 0) {
        m_history_buffer[0] = '\0';
        m_output_area->set_text("$ ");
    } else {
        append_output("Unknown command: ");
        append_output(cmd);
        append_output("\n");
    }

    append_output("$ ");
    m_input_line->clear();
}

} // namespace acos::apps
