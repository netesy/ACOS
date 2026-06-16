#include <acos/process.h>
#include <acos/runtime.h>
#include "cli_shell.h"
#include <acos/syscall.h>
#include <acos/abi/vfs.h>
#include <acos/syscall_nums.h>

namespace acos::shell {

CLIShell::CLIShell() : m_running(true) {
    ::memcpy(m_cwd, "/", 2);
    m_console_fd = static_cast<i32>(syscall(sys::SyscallNum::FileOpen, reinterpret_cast<u64>("/dev/console"), 0, 0, 0, 0));
}

void CLIShell::run() {
    char input_buffer[1024];

    acos::process::log("CLIShell: REPL loop starting...\n");
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("ACOS CLI Shell v1.0\n"), 20, 0, 0);

    while (m_running) {
        print_prompt();

        // Read line
        usize bytes_read = 0;
        char c;
        while (bytes_read < 1023) {
            i32 n = static_cast<i32>(syscall(sys::SyscallNum::FileRead, m_console_fd, reinterpret_cast<u64>(&c), 1, 0, 0));
            if (n <= 0) {
                syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0);
                continue;
            }

            if (c == '\r' || c == '\n') {
                syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
                break;
            } else if (c == '\b' || c == 127) {
                if (bytes_read > 0) {
                    bytes_read--;
                    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\b \b"), 3, 0, 0);
                }
            } else {
                input_buffer[bytes_read++] = c;
                syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(&c), 1, 0, 0);
            }
        }
        input_buffer[bytes_read] = '\0';

        if (bytes_read > 0) {
            execute_line(input_buffer);
        }
    }
}

void CLIShell::print_prompt() {
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(m_cwd), ::strlen(m_cwd), 0, 0);
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(" $ "), 3, 0, 0);
}

void CLIShell::execute_line(char* line) {
    char* argv[32];
    int argc = 0;
    bool in_quotes = false;

    char* p = line;
    while (*p && argc < 32) {
        while (*p == ' ' && !in_quotes) p++;
        if (*p == '\0') break;

        if (*p == '"') {
            in_quotes = true;
            p++;
            argv[argc++] = p;
            while (*p && (*p != '"')) p++;
        } else {
            argv[argc++] = p;
            while (*p && (*p != ' ' || in_quotes)) {
                if (*p == '"') in_quotes = !in_quotes;
                p++;
            }
        }

        if (*p) {
            *p = '\0';
            p++;
        }
        in_quotes = false;
    }

    if (argc == 0) return;

    if (::strcmp(argv[0], "help") == 0) {
        cmd_help();
    } else if (::strcmp(argv[0], "pwd") == 0) {
        cmd_pwd();
    } else if (::strcmp(argv[0], "cd") == 0) {
        cmd_cd(argc, argv);
    } else if (::strcmp(argv[0], "ls") == 0) {
        cmd_ls(argc, argv);
    } else if (::strcmp(argv[0], "exit") == 0) {
        cmd_exit();
    } else {
        execute_external(argc, argv);
    }
}

void CLIShell::cmd_help() {
    const char* msg = "Built-in commands: help, pwd, cd, ls, exit\n";
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(msg), ::strlen(msg), 0, 0);
}

void CLIShell::cmd_pwd() {
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(m_cwd), ::strlen(m_cwd), 0, 0);
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
}

void CLIShell::cmd_cd(int argc, char** argv) {
    if (argc < 2) return;
    ::memcpy(m_cwd, argv[1], ::strlen(argv[1]) + 1);
}

void CLIShell::cmd_ls(int argc, char** argv) {
    const char* path = (argc > 1) ? argv[1] : m_cwd;

    acos::abi::DirectoryEntry entries[32];
    i32 count = static_cast<i32>(syscall(
        sys::SyscallNum::FileReadDir,
        reinterpret_cast<u64>(path),
        reinterpret_cast<u64>(entries),
        32, 0, 0
    ));

    if (count < 0) {
        const char* err = "ls: cannot access directory\n";
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        return;
    }

    for (i32 i = 0; i < count; i++) {
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(entries[i].name), ::strlen(entries[i].name), 0, 0);
        if (entries[i].type == acos::abi::NodeType::Directory) {
            syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("/"), 1, 0, 0);
        }
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
    }
}

void CLIShell::cmd_exit() {
    m_running = false;
}

void CLIShell::execute_external(int argc [[maybe_unused]], char** argv) {
    char resolved_path[1024];
    u64 child_handle = static_cast<u64>(-1);

    if (argv[0][0] == '/' || argv[0][0] == '.') {
        child_handle = syscall(
            sys::SyscallNum::ProcessCreate,
            reinterpret_cast<u64>(argv[0]), 0, 0, 0, 0
        );
    } else {
        const char* paths[] = {"/bin/", "/userland/bin/", nullptr};
        for (int i = 0; paths[i]; i++) {
            ::memset(resolved_path, 0, 1024);
            ::memcpy(resolved_path, paths[i], ::strlen(paths[i]));
            ::memcpy(resolved_path + ::strlen(paths[i]), argv[0], ::strlen(argv[0]));

            child_handle = syscall(
                sys::SyscallNum::ProcessCreate,
                reinterpret_cast<u64>(resolved_path), 0, 0, 0, 0
            );
            if (child_handle != static_cast<u64>(-1)) break;
        }
    }

    if (child_handle == static_cast<u64>(-1)) {
        const char* err = "shell: command not found: ";
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(argv[0]), ::strlen(argv[0]), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
        return;
    }

    syscall(
        sys::SyscallNum::ProcessStart,
        child_handle, 0, 0, 0, 0
    );

    syscall(
        sys::SyscallNum::ThreadJoin,
        child_handle, 0, 0, 0, 0
    );
}

} // namespace acos::shell
