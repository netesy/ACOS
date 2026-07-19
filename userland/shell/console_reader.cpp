#include "console_reader.h"
#include "completion.h"
#include "history.h"
#include "variables.h"
#include <acos/syscall.h>
#include <acos/vfs.h>
#include <acos/syscall_nums.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

static void sys_write_str(i32 fd, const char* s) {
    if (!s) return;
    syscall(sys::SyscallNum::FileWrite, fd, reinterpret_cast<u64>(s), strlen(s), 0, 0);
}

void ConsoleReader::clear_to_eol(i32 fd) {
    sys_write_str(fd, "\033[K");
}

void ConsoleReader::move_cursor_left(usize& cursor_pos, i32 fd) {
    if (cursor_pos > 0) {
        cursor_pos--;
        sys_write_str(fd, "\033[D");
    }
}

void ConsoleReader::move_cursor_right(usize& cursor_pos, usize len, i32 fd) {
    if (cursor_pos < len) {
        cursor_pos++;
        sys_write_str(fd, "\033[C");
    }
}

void ConsoleReader::handle_backspace(char* buf, usize& len, usize& cursor_pos, i32 fd) {
    if (cursor_pos > 0) {
        // Shift remaining characters left
        for (usize i = cursor_pos - 1; i < len - 1; i++) {
            buf[i] = buf[i+1];
        }
        len--;
        cursor_pos--;

        // Reposition and redraw
        sys_write_str(fd, "\033[D"); // Move left
        sys_write_str(fd, "\033[s"); // Save cursor position

        // Output trailing characters
        if (cursor_pos < len) {
            sys_write_str(fd, buf + cursor_pos);
        }
        sys_write_str(fd, " "); // Overwrite last character
        sys_write_str(fd, "\033[u"); // Restore cursor position
    }
}

void ConsoleReader::handle_delete(char* buf, usize& len, usize& cursor_pos, i32 fd) {
    if (cursor_pos < len) {
        // Shift remaining characters left
        for (usize i = cursor_pos; i < len - 1; i++) {
            buf[i] = buf[i+1];
        }
        len--;

        sys_write_str(fd, "\033[s"); // Save cursor position
        if (cursor_pos < len) {
            sys_write_str(fd, buf + cursor_pos);
        }
        sys_write_str(fd, " "); // Overwrite last character
        sys_write_str(fd, "\033[u"); // Restore cursor position
    }
}

void ConsoleReader::handle_char(char* buf, usize& len, usize& cursor_pos, char c, i32 fd) {
    if (len < 1023) {
        // Shift characters right
        for (usize i = len; i > cursor_pos; i--) {
            buf[i] = buf[i-1];
        }
        buf[cursor_pos] = c;
        len++;
        cursor_pos++;

        // Echo and update trailing
        char out_c[2] = {c, '\0'};
        sys_write_str(fd, out_c);

        if (cursor_pos < len) {
            sys_write_str(fd, "\033[s"); // Save cursor
            sys_write_str(fd, buf + cursor_pos);
            sys_write_str(fd, "\033[u"); // Restore cursor
        }
    }
}

void ConsoleReader::redraw_line(const char* prompt, const char* buf, usize cursor_pos, i32 fd) {
    // Carriage return, clear whole line, print prompt and buffer, move cursor
    sys_write_str(fd, "\r");
    sys_write_str(fd, "\033[2K");
    sys_write_str(fd, prompt);
    sys_write_str(fd, buf);

    // Position cursor at cursor_pos
    sys_write_str(fd, "\r");
    sys_write_str(fd, prompt);
    for (usize i = 0; i < cursor_pos; i++) {
        sys_write_str(fd, "\033[C");
    }
}

bool ConsoleReader::read_line(i32 console_fd, const char* cwd, char* out_buf, usize max_len) {
    if (max_len == 0 || !out_buf) return false;

    out_buf[0] = '\0';
    usize len = 0;
    usize cursor_pos = 0;

    // Render customized prompt first
    char prompt[256];
    const char* prompt_fmt = VariablesManager::get("PROMPT");
    if (prompt_fmt && prompt_fmt[0] != '\0') {
        // Quick format parsing
        usize p_len = 0;
        for (int i = 0; prompt_fmt[i] && p_len < 250; i++) {
            if (prompt_fmt[i] == '\\' && prompt_fmt[i+1]) {
                i++;
                if (prompt_fmt[i] == 'u') {
                    const char* user = VariablesManager::get("USER");
                    usize ulen = strlen(user);
                    memcpy(prompt + p_len, user, ulen);
                    p_len += ulen;
                } else if (prompt_fmt[i] == 'W') {
                    // Base directory name of CWD
                    int last_slash = -1;
                    for (int k = 0; cwd[k]; k++) {
                        if (cwd[k] == '/') last_slash = k;
                    }
                    if (last_slash != -1 && cwd[last_slash + 1]) {
                        const char* base = cwd + last_slash + 1;
                        usize blen = strlen(base);
                        memcpy(prompt + p_len, base, blen);
                        p_len += blen;
                    } else {
                        prompt[p_len++] = '/';
                    }
                } else {
                    prompt[p_len++] = prompt_fmt[i];
                }
            } else {
                prompt[p_len++] = prompt_fmt[i];
            }
        }
        prompt[p_len] = '\0';
    } else {
        usize clen = strlen(cwd);
        memcpy(prompt, cwd, clen);
        memcpy(prompt + clen, " $ ", 4);
    }

    sys_write_str(console_fd, prompt);

    int history_index = HistoryManager::count(); // Pointing to past-the-end (fresh command)
    static char saved_current_input[1024] = {0};

    // ANSI escape code state machine states
    enum State {
        Normal,
        Escape,
        Bracket,
        DeleteKey
    };
    State state = Normal;

    while (true) {
        char c;
        i32 n = static_cast<i32>(syscall(sys::SyscallNum::FileRead, console_fd, reinterpret_cast<u64>(&c), 1, 0, 0));
        if (n <= 0) {
            syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0);
            continue;
        }

        // State Machine for Escape Sequences
        if (state == Escape) {
            if (c == '[') {
                state = Bracket;
            } else {
                state = Normal;
            }
            continue;
        } else if (state == Bracket) {
            if (c == 'D') { // Left Arrow
                move_cursor_left(cursor_pos, console_fd);
                state = Normal;
            } else if (c == 'C') { // Right Arrow
                move_cursor_right(cursor_pos, len, console_fd);
                state = Normal;
            } else if (c == 'A') { // Up Arrow (History Back)
                if (history_index > 0) {
                    if (history_index == HistoryManager::count()) {
                        // Save current uncommitted typing
                        memcpy(saved_current_input, out_buf, len);
                        saved_current_input[len] = '\0';
                    }
                    history_index--;
                    const char* hist = HistoryManager::get(history_index);
                    if (hist) {
                        len = strlen(hist);
                        memcpy(out_buf, hist, len);
                        out_buf[len] = '\0';
                        cursor_pos = len;
                        redraw_line(prompt, out_buf, cursor_pos, console_fd);
                    }
                }
                state = Normal;
            } else if (c == 'B') { // Down Arrow (History Forward)
                if (history_index < HistoryManager::count()) {
                    history_index++;
                    if (history_index == HistoryManager::count()) {
                        len = strlen(saved_current_input);
                        memcpy(out_buf, saved_current_input, len);
                        out_buf[len] = '\0';
                        cursor_pos = len;
                        redraw_line(prompt, out_buf, cursor_pos, console_fd);
                    } else {
                        const char* hist = HistoryManager::get(history_index);
                        if (hist) {
                            len = strlen(hist);
                            memcpy(out_buf, hist, len);
                            out_buf[len] = '\0';
                            cursor_pos = len;
                            redraw_line(prompt, out_buf, cursor_pos, console_fd);
                        }
                    }
                }
                state = Normal;
            } else if (c == 'H') { // Home Key
                cursor_pos = 0;
                redraw_line(prompt, out_buf, cursor_pos, console_fd);
                state = Normal;
            } else if (c == 'F') { // End Key
                cursor_pos = len;
                redraw_line(prompt, out_buf, cursor_pos, console_fd);
                state = Normal;
            } else if (c == '3') {
                state = DeleteKey;
            } else {
                state = Normal;
            }
            continue;
        } else if (state == DeleteKey) {
            if (c == '~') { // Delete
                handle_delete(out_buf, len, cursor_pos, console_fd);
            }
            state = Normal;
            continue;
        }

        // Normal character processing
        if (c == 0x1b) {
            state = Escape;
            continue;
        }

        if (c == 0x03) { // Ctrl+C
            sys_write_str(console_fd, "^C\n");
            out_buf[0] = '\0';
            len = 0;
            cursor_pos = 0;
            sys_write_str(console_fd, prompt);
            history_index = HistoryManager::count();
            continue;
        } else if (c == 0x04) { // Ctrl+D
            if (len == 0) {
                sys_write_str(console_fd, "exit\n");
                memcpy(out_buf, "exit", 5);
                return true;
            }
            continue;
        } else if (c == 0x0c) { // Ctrl+L
            sys_write_str(console_fd, "\033[2J\033[H");
            redraw_line(prompt, out_buf, cursor_pos, console_fd);
            continue;
        }

        if (c == '\r' || c == '\n') {
            sys_write_str(console_fd, "\n");
            out_buf[len] = '\0';
            return true;
        } else if (c == '\b' || c == 127) {
            handle_backspace(out_buf, len, cursor_pos, console_fd);
        } else if (c == 9) { // Tab key (Completion)
            // 1. Find partial word from current buffer up to cursor_pos
            int word_start = cursor_pos;
            while (word_start > 0 && out_buf[word_start-1] != ' ' && out_buf[word_start-1] != '\t') {
                word_start--;
            }

            static char partial_word[256];
            usize p_len = 0;
            for (int k = word_start; k < (int)cursor_pos; k++) {
                if (p_len < 255) partial_word[p_len++] = out_buf[k];
            }
            partial_word[p_len] = '\0';

            char completed[256];
            bool is_dir = false;
            int n_matches = CompletionManager::complete(cwd, partial_word, completed, is_dir);

            if (n_matches == 1) {
                // Suffix found! Insert into buffer
                for (int k = 0; completed[k]; k++) {
                    handle_char(out_buf, len, cursor_pos, completed[k], console_fd);
                }
                // Append suffix descriptor
                if (is_dir) {
                    handle_char(out_buf, len, cursor_pos, '/', console_fd);
                } else {
                    handle_char(out_buf, len, cursor_pos, ' ', console_fd);
                }
            } else if (n_matches > 1) {
                // Multiple matches. Since we can't easily fetch names without rewrite,
                // we can just emit a bell or optionally reprint.
                sys_write_str(console_fd, "\x07"); // Beep
            } else {
                sys_write_str(console_fd, "\x07"); // Beep
            }
        } else {
            // Printable char
            if (c >= 32 && c <= 126) {
                handle_char(out_buf, len, cursor_pos, c, console_fd);
            }
        }
    }
}

} // namespace acos::shell
