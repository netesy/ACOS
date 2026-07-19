#pragma once
#include <acos/types.h>

namespace acos::shell {

class CLIShell {
public:
    CLIShell();
    ~CLIShell() = default;

    void run();

private:
    void execute_startup_scripts();
    void perform_command_substitution(char* buffer);

    char m_cwd[1024];
    bool m_running;
    i32 m_console_fd;
};

} // namespace acos::shell
