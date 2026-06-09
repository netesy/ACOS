#pragma once
#include <acos/types.h>

namespace acos::shell {

class CLIShell {
public:
    CLIShell();
    ~CLIShell() = default;

    void run();

private:
    void print_prompt();
    void execute_line(char* line);

    // Built-ins
    void cmd_help();
    void cmd_pwd();
    void cmd_cd(int argc, char** argv);
    void cmd_ls(int argc, char** argv);
    void cmd_exit();

    void execute_external(int argc, char** argv);

    char m_cwd[1024];
    bool m_running;
    i32 m_console_fd;
};

} // namespace acos::shell
