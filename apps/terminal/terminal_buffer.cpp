#include "terminal_buffer.h"
#include <acos/process.h>
#include <acos/runtime.h>

namespace acos::apps {

TerminalBuffer::TerminalBuffer()
    : m_cols(MAX_COLS), m_rows(MAX_ROWS),
      m_cursor_col(0), m_cursor_row(0),
      m_history_count(0), m_history_head(0),
      m_scroll_offset(0) {

    for (usize i = 0; i < SCROLLBACK_LIMIT; i++) {
        m_history[i] = nullptr;
    }

    // Initialize screen rows in history
    for (usize i = 0; i < m_rows; i++) {
        Cell* line = static_cast<Cell*>(memory::malloc(m_cols * sizeof(Cell)));
        for (usize j = 0; j < m_cols; j++) {
            line[j] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
        }
        m_history[i] = line;
    }
    m_history_count = m_rows;
}

TerminalBuffer::~TerminalBuffer() {
    for (usize i = 0; i < SCROLLBACK_LIMIT; i++) {
        if (m_history[i]) {
            memory::free(m_history[i]);
            m_history[i] = nullptr;
        }
    }
}

void TerminalBuffer::resize(usize cols, usize rows) {
    if (cols == 0 || rows == 0) return;
    m_cols = cols;
    m_rows = rows;
    m_cursor_col = 0;
    m_cursor_row = 0;
}

void TerminalBuffer::clear_screen() {
    for (usize r = 0; r < m_history_count; r++) {
        Cell* line = m_history[(m_history_head + r) % SCROLLBACK_LIMIT];
        if (line) {
            for (usize c = 0; c < m_cols; c++) {
                line[c] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
            }
        }
    }
    m_cursor_col = 0;
    m_cursor_row = 0;
}

void TerminalBuffer::clear_line_from_cursor() {
    usize real_row = (m_history_head + m_cursor_row) % SCROLLBACK_LIMIT;
    Cell* line = m_history[real_row];
    if (line) {
        for (usize c = m_cursor_col; c < m_cols; c++) {
            line[c] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
        }
    }
}

void TerminalBuffer::clear_line_to_cursor() {
    usize real_row = (m_history_head + m_cursor_row) % SCROLLBACK_LIMIT;
    Cell* line = m_history[real_row];
    if (line) {
        for (usize c = 0; c <= m_cursor_col && c < m_cols; c++) {
            line[c] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
        }
    }
}

void TerminalBuffer::clear_line() {
    usize real_row = (m_history_head + m_cursor_row) % SCROLLBACK_LIMIT;
    Cell* line = m_history[real_row];
    if (line) {
        for (usize c = 0; c < m_cols; c++) {
            line[c] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
        }
    }
}

void TerminalBuffer::put_char(char c, u32 fg, u32 bg, u8 flags) {
    if (m_cursor_col >= m_cols) {
        new_line(bg);
    }

    usize real_row = (m_history_head + m_cursor_row) % SCROLLBACK_LIMIT;
    Cell* line = m_history[real_row];
    if (line) {
        line[m_cursor_col] = {c, fg, bg, flags};
        m_cursor_col++;
    }
}

void TerminalBuffer::backspace() {
    if (m_cursor_col > 0) {
        m_cursor_col--;
        usize real_row = (m_history_head + m_cursor_row) % SCROLLBACK_LIMIT;
        Cell* line = m_history[real_row];
        if (line) {
            line[m_cursor_col] = {' ', DEFAULT_FG, DEFAULT_BG, 0};
        }
    }
}

void TerminalBuffer::new_line(u32 bg) {
    if (m_cursor_row + 1 >= m_rows) {
        scroll_screen_up(bg);
    } else {
        m_cursor_row++;
    }
    m_cursor_col = 0;
}

void TerminalBuffer::scroll_screen_up(u32 bg) {
    // If we have room in the history, just grow m_history_count and advance m_history_head
    if (m_history_count < SCROLLBACK_LIMIT) {
        Cell* newline = static_cast<Cell*>(memory::malloc(m_cols * sizeof(Cell)));
        for (usize j = 0; j < m_cols; j++) {
            newline[j] = {' ', DEFAULT_FG, bg, 0};
        }
        m_history[m_history_count] = newline;
        m_history_count++;
        m_history_head++;
    } else {
        // Free oldest line and reuse its slot
        Cell* oldline = m_history[m_history_head];
        for (usize j = 0; j < m_cols; j++) {
            oldline[j] = {' ', DEFAULT_FG, bg, 0};
        }
        m_history_head = (m_history_head + 1) % SCROLLBACK_LIMIT;
    }
    m_cursor_col = 0;
}

void TerminalBuffer::set_cursor(usize col, usize row) {
    if (col < m_cols) m_cursor_col = col;
    if (row < m_rows) m_cursor_row = row;
}

Cell TerminalBuffer::get_cell(usize col, usize row_in_view) const {
    if (col >= m_cols || row_in_view >= m_rows) {
        return {' ', DEFAULT_FG, DEFAULT_BG, 0};
    }

    // Compensate for scroll offset
    int history_index = static_cast<int>(m_history_head) + static_cast<int>(row_in_view) - m_scroll_offset;
    if (history_index < 0) {
        return {' ', DEFAULT_FG, DEFAULT_BG, 0};
    }

    usize real_row = static_cast<usize>(history_index) % SCROLLBACK_LIMIT;
    Cell* line = m_history[real_row];
    if (line) {
        return line[col];
    }
    return {' ', DEFAULT_FG, DEFAULT_BG, 0};
}

void TerminalBuffer::scroll(int delta) {
    m_scroll_offset += delta;
    if (m_scroll_offset < 0) m_scroll_offset = 0;

    int max_scroll = static_cast<int>(m_history_count) - static_cast<int>(m_rows);
    if (max_scroll < 0) max_scroll = 0;
    if (m_scroll_offset > max_scroll) m_scroll_offset = max_scroll;
}

} // namespace acos::apps
