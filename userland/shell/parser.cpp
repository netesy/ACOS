#include "parser.h"
#include "variables.h"
#include <acos/process.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

char* CommandLineParser::str_trim(char* s) {
    if (!s) return nullptr;
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') {
        s++;
    }
    if (*s == '\0') return s;
    char* end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
        *end = '\0';
        end--;
    }
    return s;
}

void CommandLineParser::expand_variables(const char* src, char* dest, usize dest_max) {
    usize s_idx = 0;
    usize d_idx = 0;

    while (src[s_idx] && d_idx < dest_max - 1) {
        if (src[s_idx] == '$') {
            s_idx++; // skip '$'
            if (src[s_idx] == '\0') {
                dest[d_idx++] = '$';
                break;
            }

            // Extract variable name
            char var_name[128];
            usize vn_idx = 0;
            if (src[s_idx] == '?') {
                var_name[vn_idx++] = '?';
                var_name[vn_idx] = '\0';
                s_idx++;
            } else {
                while (src[s_idx] && vn_idx < 127 &&
                       ((src[s_idx] >= 'a' && src[s_idx] <= 'z') ||
                        (src[s_idx] >= 'A' && src[s_idx] <= 'Z') ||
                        (src[s_idx] >= '0' && src[s_idx] <= '9') ||
                        src[s_idx] == '_')) {
                    var_name[vn_idx++] = src[s_idx++];
                }
                var_name[vn_idx] = '\0';
            }

            if (vn_idx > 0) {
                const char* val = VariablesManager::get(var_name);
                if (val) {
                    for (usize i = 0; val[i] && d_idx < dest_max - 1; i++) {
                        dest[d_idx++] = val[i];
                    }
                }
            } else {
                // If it was just $ but no name (e.g. at end or followed by space)
                dest[d_idx++] = '$';
            }
        } else {
            dest[d_idx++] = src[s_idx++];
        }
    }
    dest[d_idx] = '\0';
}

bool CommandLineParser::parse(const char* input_line, Pipeline& out_pipeline) {
    out_pipeline.command_count = 0;

    if (!input_line || input_line[0] == '\0') return false;

    // Buffer to play with
    static char line_buf[2048];
    usize len = 0;
    while (input_line[len] && len < 2047) {
        line_buf[len] = input_line[len];
        len++;
    }
    line_buf[len] = '\0';

    // Phase 1: Split into commands by pipeline character '|'
    char* cmd_strings[16];
    int cmd_count = 0;

    char* p = line_buf;
    bool in_single = false;
    bool in_double = false;
    char* current_start = p;

    while (*p) {
        if (*p == '\'' && !in_double) {
            in_single = !in_single;
        } else if (*p == '"' && !in_single) {
            in_double = !in_double;
        } else if (*p == '|' && !in_single && !in_double) {
            *p = '\0';
            cmd_strings[cmd_count++] = str_trim(current_start);
            current_start = p + 1;
            if (cmd_count >= 16) break;
        }
        p++;
    }
    if (cmd_count < 16) {
        cmd_strings[cmd_count++] = str_trim(current_start);
    }

    out_pipeline.command_count = cmd_count;

    // Phase 2: For each command string, parse arguments and redirections
    for (int i = 0; i < cmd_count; i++) {
        Command& cmd = out_pipeline.commands[i];
        cmd.argc = 0;
        cmd.redirection_count = 0;

        char* cmd_str = cmd_strings[i];
        if (!cmd_str || cmd_str[0] == '\0') continue;

        // Extract redirections: >, >>, <
        // We will scan the command string outside quotes, extract them, and terminate the string
        char* sc = cmd_str;
        in_single = false;
        in_double = false;

        while (*sc) {
            if (*sc == '\'' && !in_double) {
                in_single = !in_single;
            } else if (*sc == '"' && !in_single) {
                in_double = !in_double;
            } else if ((*sc == '>' || *sc == '<') && !in_single && !in_double) {
                char symbol = *sc;
                bool append = false;
                char* file_start = nullptr;

                if (symbol == '>' && *(sc + 1) == '>') {
                    append = true;
                    *sc = '\0';
                    *(sc + 1) = '\0';
                    file_start = sc + 2;
                } else {
                    *sc = '\0';
                    file_start = sc + 1;
                }

                // Parse out the filename
                file_start = str_trim(file_start);
                // Cut at next space or redir symbol in file_start if any
                char* fc = file_start;
                bool file_in_single = false;
                bool file_in_double = false;
                while (*fc) {
                    if (*fc == '\'' && !file_in_double) file_in_single = !file_in_single;
                    else if (*fc == '"' && !file_in_single) file_in_double = !file_in_double;
                    else if ((*fc == ' ' || *fc == '\t' || *fc == '>' || *fc == '<') && !file_in_single && !file_in_double) {
                        *fc = '\0';
                        break;
                    }
                    fc++;
                }

                if (cmd.redirection_count < 4 && file_start && file_start[0] != '\0') {
                    Redirection& redir = cmd.redirections[cmd.redirection_count++];
                    redir.is_input = (symbol == '<');
                    redir.is_output = (symbol == '>');
                    redir.is_append = append;

                    // Copy filename
                    usize flen = 0;
                    while (file_start[flen] && flen < 255) {
                        redir.file[flen] = file_start[flen];
                        flen++;
                    }
                    redir.file[flen] = '\0';
                }

                // Rewind scan check if we did double char
                if (append) sc++;
            }
            sc++;
        }

        // Parse remaining string into argv
        cmd_str = str_trim(cmd_str);

        char* token_p = cmd_str;
        in_single = false;
        in_double = false;

        while (*token_p && cmd.argc < 64) {
            // Trim leading space
            while (*token_p == ' ' || *token_p == '\t') token_p++;
            if (*token_p == '\0') break;

            char* arg_start = token_p;
            static char raw_arg[1024];
            usize raw_idx = 0;

            bool is_quoted = false;

            while (*token_p) {
                if (*token_p == '\'' && !in_double) {
                    in_single = !in_single;
                    is_quoted = true;
                    token_p++;
                } else if (*token_p == '"' && !in_single) {
                    in_double = !in_double;
                    is_quoted = true;
                    token_p++;
                } else if ((*token_p == ' ' || *token_p == '\t') && !in_single && !in_double) {
                    break;
                } else {
                    // Extract characters based on quotes
                    if (in_single) {
                        // Inside single quotes: raw copy, no var expansion
                        if (raw_idx < 1023) raw_arg[raw_idx++] = *token_p;
                        token_p++;
                    } else if (in_double) {
                        // Inside double quotes: we will expand variables later, copy raw for now
                        if (raw_idx < 1023) raw_arg[raw_idx++] = *token_p;
                        token_p++;
                    } else {
                        // Unquoted
                        if (raw_idx < 1023) raw_arg[raw_idx++] = *token_p;
                        token_p++;
                    }
                }
            }
            raw_arg[raw_idx] = '\0';

            // Now perform variable expansion on raw_arg if it wasn't single-quoted
            // (or to be precise, if it's unquoted or double-quoted, we expand)
            static char expanded_arg[1024];
            if (is_quoted && !in_single && !in_double && arg_start[0] == '\'') {
                // If it was fully single quoted, keep raw
                usize raw_len = 0;
                while (raw_arg[raw_len] && raw_len < 1023) {
                    expanded_arg[raw_len] = raw_arg[raw_len];
                    raw_len++;
                }
                expanded_arg[raw_len] = '\0';
            } else {
                expand_variables(raw_arg, expanded_arg, 1024);
            }

            // Allocate and save to argv
            usize elen = strlen(expanded_arg);
            char* saved_arg = static_cast<char*>(memory::kmalloc(elen + 1));
            if (saved_arg) {
                memcpy(saved_arg, expanded_arg, elen + 1);
                cmd.argv[cmd.argc++] = saved_arg;
            }
        }
    }

    return out_pipeline.command_count > 0;
}

} // namespace acos::shell
