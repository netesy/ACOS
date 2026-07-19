#pragma once
#include <acos/types.h>

namespace acos::shell {

struct Redirection {
    char file[256];
    bool is_input;      // <
    bool is_append;     // >>
    bool is_output;     // >
};

struct Command {
    char* argv[64];
    int argc;
    Redirection redirections[4];
    int redirection_count;
};

struct Pipeline {
    Command commands[16];
    int command_count;
};

class CommandLineParser {
public:
    static bool parse(const char* input_line, Pipeline& out_pipeline);

private:
    static void expand_variables(const char* src, char* dest, usize dest_max);
    static char* str_trim(char* s);
};

} // namespace acos::shell
