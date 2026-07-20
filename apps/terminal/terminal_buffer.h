#pragma once
#include <acos/types.h>

namespace acos::apps {

struct Cell {
    char ch;
    u32 fg;
    u32 bg;
    u8 flags;
};

class TerminalBuffer {
public:
    static constexpr usize MAX_COLS = 80;
    static constexpr usize MAX_ROWS = 24;
    static constexpr usize SCROLLBACK_LIMIT = 500;

    static constexpr u32 DEFAULT_BG = 0xFF181818;
    static constexpr u32 DEFAULT_FG = 0xFFCCCCCC;

    TerminalBuffer();
    ~TerminalBuffer();

    void resize(usize cols, usize rows);

    void clear_screen();
    void clear_line_from_cursor();
    void clear_line_to_cursor();
    void clear_line();

    void put_char(char c, u32 fg, u32 bg, u8 flags);
    void backspace();
    void new_line(u32 bg);

    usize cols() const { return m_cols; }
    usize rows() const { return m_rows; }

    usize cursor_col() const { return m_cursor_col; }
    usize cursor_row() const { return m_cursor_row; }
    void set_cursor(usize col, usize row);

    Cell get_cell(usize col, usize row_in_view) const;

    // Scroll offset inside the scrollback history (0 means aligned with current screen view)
    int scroll_offset() const { return m_scroll_offset; }
    void scroll(int delta);

private:
    void scroll_screen_up(u32 bg);

    usize m_cols;
    usize m_rows;

    usize m_cursor_col;
    usize m_cursor_row;

    // Buffer is a circular list of lines
    Cell* m_history[SCROLLBACK_LIMIT];
    usize m_history_count;
    usize m_history_head;

    int m_scroll_offset;
};

} // namespace acos::apps
