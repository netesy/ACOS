#pragma once
#include <acos/types.h>

namespace acos::shell {

class ConsoleReader {
public:
    static bool read_line(i32 console_fd, const char* cwd, char* out_buf, usize max_len);

private:
    static void handle_backspace(char* buf, usize& len, usize& cursor_pos, i32 fd);
    static void handle_delete(char* buf, usize& len, usize& cursor_pos, i32 fd);
    static void handle_char(char* buf, usize& len, usize& cursor_pos, char c, i32 fd);
    static void move_cursor_left(usize& cursor_pos, i32 fd);
    static void move_cursor_right(usize& cursor_pos, usize len, i32 fd);

    // Redraw helpers
    static void redraw_line(const char* prompt, const char* buf, usize cursor_pos, i32 fd);
    static void clear_to_eol(i32 fd);
};

} // namespace acos::shell
