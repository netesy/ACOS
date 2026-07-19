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

            if (c >= 32 && c <= 126) {
                acos::process::log("[CLI] received '");
                char s[2] = {c, '\0'};
                acos::process::log(s);
                acos::process::log("'\n");
            } else if (c == '\b' || c == 127) {
                acos::process::log("[CLI] received Backspace\n");
            } else if (c == '\n' || c == '\r') {
                acos::process::log("[CLI] received Enter\n");
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
    } else if (::strcmp(argv[0], "version") == 0) {
        cmd_version();
    } else if (::strcmp(argv[0], "clear") == 0) {
        cmd_clear();
    } else if (::strcmp(argv[0], "echo") == 0) {
        cmd_echo(argc, argv);
    } else if (::strcmp(argv[0], "pwd") == 0) {
        cmd_pwd();
    } else if (::strcmp(argv[0], "cd") == 0) {
        cmd_cd(argc, argv);
    } else if (::strcmp(argv[0], "ls") == 0) {
        cmd_ls(argc, argv);
    } else if (::strcmp(argv[0], "cat") == 0) {
        cmd_cat(argc, argv);
    } else if (::strcmp(argv[0], "exit") == 0) {
        cmd_exit();
    } else {
        const char* err1 = "Unknown command: ";
        const char* err2 = "\nType \"help\" for a list of commands.\n";
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err1), ::strlen(err1), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(argv[0]), ::strlen(argv[0]), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err2), ::strlen(err2), 0, 0);
    }
}

void CLIShell::cmd_help() {
    const char* msg = "ACOS CLI Help. Available built-in commands:\n"
                      "  help         List all available commands\n"
                      "  version      Print ACOS version information\n"
                      "  clear        Clear the screen\n"
                      "  echo [text]  Print text arguments\n"
                      "  pwd          Print current working directory\n"
                      "  cd [dir]     Change current working directory\n"
                      "  ls [dir]     List directory contents\n"
                      "  cat [file]   Display file contents\n"
                      "  exit         Exit the shell cleanly\n";
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(msg), ::strlen(msg), 0, 0);
}

void CLIShell::cmd_version() {
    const char* msg = "ACOS Adaptive Capability Operating System v1.0\n";
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(msg), ::strlen(msg), 0, 0);
}

void CLIShell::cmd_clear() {
    const char* msg = "\033[2J\033[H";
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(msg), ::strlen(msg), 0, 0);
}

void CLIShell::cmd_echo(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(argv[i]), ::strlen(argv[i]), 0, 0);
        if (i < argc - 1) {
            syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(" "), 1, 0, 0);
        }
    }
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
}

void CLIShell::cmd_pwd() {
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(m_cwd), ::strlen(m_cwd), 0, 0);
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
}

void CLIShell::cmd_cd(int argc, char** argv) {
    if (argc < 2) {
        ::memcpy(m_cwd, "/", 2);
        return;
    }

    const char* dest = argv[1];
    if (dest[0] == '/') {
        ::memcpy(m_cwd, dest, ::strlen(dest) + 1);
    } else {
        char resolved_path[1024];
        ::memset(resolved_path, 0, 1024);
        ::memcpy(resolved_path, m_cwd, ::strlen(m_cwd));
        usize cwd_len = ::strlen(m_cwd);
        if (cwd_len > 1 && m_cwd[cwd_len - 1] != '/') {
            resolved_path[cwd_len] = '/';
            cwd_len++;
        }
        ::memcpy(resolved_path + cwd_len, dest, ::strlen(dest));
        ::memcpy(m_cwd, resolved_path, ::strlen(resolved_path) + 1);
    }
}

void CLIShell::cmd_ls(int argc, char** argv) {
    const char* path = (argc > 1) ? argv[1] : m_cwd;
    char resolved_path[1024];

    if (path[0] != '/') {
        ::memset(resolved_path, 0, 1024);
        ::memcpy(resolved_path, m_cwd, ::strlen(m_cwd));
        usize cwd_len = ::strlen(m_cwd);
        if (cwd_len > 1 && m_cwd[cwd_len - 1] != '/') {
            resolved_path[cwd_len] = '/';
            cwd_len++;
        }
        ::memcpy(resolved_path + cwd_len, path, ::strlen(path));
        path = resolved_path;
    }

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

void CLIShell::cmd_cat(int argc, char** argv) {
    if (argc < 2) {
        const char* err = "Usage: cat <file>\n";
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        return;
    }

    char resolved_path[1024];
    const char* path = argv[1];
    if (path[0] != '/') {
        // Resolve relative path against m_cwd
        ::memset(resolved_path, 0, 1024);
        ::memcpy(resolved_path, m_cwd, ::strlen(m_cwd));
        usize cwd_len = ::strlen(m_cwd);
        if (cwd_len > 1 && m_cwd[cwd_len - 1] != '/') {
            resolved_path[cwd_len] = '/';
            cwd_len++;
        }
        ::memcpy(resolved_path + cwd_len, path, ::strlen(path));
        path = resolved_path;
    }

    i32 fd = static_cast<i32>(syscall(sys::SyscallNum::FileOpen, reinterpret_cast<u64>(path), 0, 0, 0, 0));
    if (fd < 0) {
        const char* err = "cat: cannot open file: ";
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(argv[1]), ::strlen(argv[1]), 0, 0);
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
        return;
    }

    char buf[256];
    while (true) {
        i32 n = static_cast<i32>(syscall(sys::SyscallNum::FileRead, static_cast<u64>(fd), reinterpret_cast<u64>(buf), 256, 0, 0));
        if (n <= 0) break;
        syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(buf), static_cast<u64>(n), 0, 0);
    }

    syscall(sys::SyscallNum::FileClose, static_cast<u64>(fd), 0, 0, 0, 0);
}

void CLIShell::cmd_exit() {
    m_running = false;
    syscall(sys::SyscallNum::Exit, 0, 0, 0, 0, 0);
}

void CLIShell::execute_external(int argc [[maybe_unused]], char** argv) {
    // Simply print unknown command message
    const char* err1 = "Unknown command: ";
    const char* err2 = "\nType \"help\" for a list of commands.\n";
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err1), ::strlen(err1), 0, 0);
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(argv[0]), ::strlen(argv[0]), 0, 0);
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>(err2), ::strlen(err2), 0, 0);
}

} // namespace acos::shell
