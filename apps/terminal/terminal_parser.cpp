#include "terminal_parser.h"
#include <acos/process.h>
#include <acos/runtime.h>

namespace acos::apps {

static const u32 ansi_palette[8] = {
    0xFF000000, // Black
    0xFFFF5555, // Red
    0xFF55FF55, // Green
    0xFFFFFF55, // Yellow
    0xFF5555FF, // Blue
    0xFFFF55FF, // Magenta
    0xFF55FFFF, // Cyan
    0xFFCCCCCC  // White
};

TerminalParser::TerminalParser(TerminalBuffer* buffer)
    : m_buffer(buffer), m_state(Normal),
      m_fg(TerminalBuffer::DEFAULT_FG), m_bg(TerminalBuffer::DEFAULT_BG), m_flags(0),
      m_param_count(0), m_param_has_digit(false) {
    for (usize i = 0; i < MAX_PARAMS; i++) {
        m_params[i] = 0;
    }
}

TerminalParser::~TerminalParser() {}

void TerminalParser::write(const char* data, usize len) {
    for (usize i = 0; i < len; i++) {
        process_char(data[i]);
    }
}

void TerminalParser::process_char(char c) {
    switch (m_state) {
        case Normal:
            if (c == 0x1B) {
                m_state = Escape;
            } else if (c == '\r') {
                m_buffer->set_cursor(0, m_buffer->cursor_row());
            } else if (c == '\n') {
                m_buffer->new_line(m_bg);
            } else if (c == '\b') {
                m_buffer->backspace();
            } else if (c >= 32 && c <= 126) {
                m_buffer->put_char(c, m_fg, m_bg, m_flags);
            }
            break;

        case Escape:
            if (c == '[') {
                m_state = CSI;
                m_param_count = 0;
                m_params[0] = 0;
                m_param_has_digit = false;
            } else {
                m_state = Normal;
            }
            break;

        case CSI:
            if (c >= '0' && c <= '9') {
                m_params[m_param_count] = m_params[m_param_count] * 10 + (c - '0');
                m_param_has_digit = true;
            } else if (c == ';') {
                if (m_param_count < MAX_PARAMS - 1) {
                    m_param_count++;
                    m_params[m_param_count] = 0;
                    m_param_has_digit = false;
                }
            } else if (c >= 0x40 && c <= 0x7E) {
                if (m_param_has_digit) {
                    m_param_count++;
                }
                handle_csi_command(c);
                m_state = Normal;
            }
            break;
    }
}

void TerminalParser::handle_csi_command(char final_char) {
    int p1 = m_param_count > 0 ? m_params[0] : 1;
    int p2 = m_param_count > 1 ? m_params[1] : 1;

    switch (final_char) {
        case 'H':
        case 'f': { // Cursor position (1-based index)
            usize row = (p1 > 0) ? static_cast<usize>(p1 - 1) : 0;
            usize col = (p2 > 0) ? static_cast<usize>(p2 - 1) : 0;
            m_buffer->set_cursor(col, row);
            break;
        }

        case 'A': { // Cursor Up
            usize row = m_buffer->cursor_row();
            int delta = p1 > 0 ? p1 : 1;
            if (row >= static_cast<usize>(delta)) {
                m_buffer->set_cursor(m_buffer->cursor_col(), row - delta);
            } else {
                m_buffer->set_cursor(m_buffer->cursor_col(), 0);
            }
            break;
        }

        case 'B': { // Cursor Down
            usize row = m_buffer->cursor_row();
            int delta = p1 > 0 ? p1 : 1;
            m_buffer->set_cursor(m_buffer->cursor_col(), row + delta);
            break;
        }

        case 'C': { // Cursor Forward
            usize col = m_buffer->cursor_col();
            int delta = p1 > 0 ? p1 : 1;
            m_buffer->set_cursor(col + delta, m_buffer->cursor_row());
            break;
        }

        case 'D': { // Cursor Backward
            usize col = m_buffer->cursor_col();
            int delta = p1 > 0 ? p1 : 1;
            if (col >= static_cast<usize>(delta)) {
                m_buffer->set_cursor(col - delta, m_buffer->cursor_row());
            } else {
                m_buffer->set_cursor(0, m_buffer->cursor_row());
            }
            break;
        }

        case 'J': { // Erase in Display
            int mode = m_param_count > 0 ? m_params[0] : 0;
            if (mode == 2) {
                m_buffer->clear_screen();
            }
            break;
        }

        case 'K': { // Erase in Line
            int mode = m_param_count > 0 ? m_params[0] : 0;
            if (mode == 0) {
                m_buffer->clear_line_from_cursor();
            } else if (mode == 1) {
                m_buffer->clear_line_to_cursor();
            } else if (mode == 2) {
                m_buffer->clear_line();
            }
            break;
        }

        case 'm': { // SGR (Select Graphic Rendition)
            parse_sgr();
            break;
        }
    }
}

void TerminalParser::parse_sgr() {
    if (m_param_count == 0) {
        // ESC [m is equivalent to ESC [0m (Reset)
        m_fg = TerminalBuffer::DEFAULT_FG;
        m_bg = TerminalBuffer::DEFAULT_BG;
        m_flags = 0;
        return;
    }

    for (usize i = 0; i < m_param_count; i++) {
        int param = m_params[i];

        if (param == 0) { // Reset
            m_fg = TerminalBuffer::DEFAULT_FG;
            m_bg = TerminalBuffer::DEFAULT_BG;
            m_flags = 0;
        } else if (param == 1) { // Bold
            m_flags |= 1;
        } else if (param == 4) { // Underline
            m_flags |= 2;
        } else if (param == 7) { // Reverse Video
            m_flags |= 4;
        } else if (param >= 30 && param <= 37) { // Foreground Color
            m_fg = ansi_palette[param - 30];
        } else if (param == 39) { // Default Foreground
            m_fg = TerminalBuffer::DEFAULT_FG;
        } else if (param >= 40 && param <= 47) { // Background Color
            m_bg = ansi_palette[param - 40];
        } else if (param == 49) { // Default Background
            m_bg = TerminalBuffer::DEFAULT_BG;
        }
    }
}

} // namespace acos::apps
