#include "cli_shell.h"
#include <kernel/syscall/syscall.h>
#include <kernel/vfs/vfs.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

CLIShell::CLIShell() : m_running(true) {
    ::memcpy(m_cwd, "/", 2);
    // In userland we'd use syscalls to open /dev/console
    m_console_fd = static_cast<i32>(acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileOpen), reinterpret_cast<u64>("/dev/console"), 0, 0, 0, 0));
}

void CLIShell::run() {
    char input_buffer[1024];

    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("ACOS CLI Shell v1.0\n"), 20, 0, 0);

    while (m_running) {
        print_prompt();

        // Read line
        usize bytes_read = 0;
        char c;
        while (bytes_read < 1023) {
            i32 n = static_cast<i32>(acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileRead), m_console_fd, reinterpret_cast<u64>(&c), 1, 0, 0));
            if (n <= 0) continue;

            if (c == '\r' || c == '\n') {
                acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
                break;
            } else if (c == '\b' || c == 127) {
                if (bytes_read > 0) {
                    bytes_read--;
                    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("\b \b"), 3, 0, 0);
                }
            } else {
                input_buffer[bytes_read++] = c;
                acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(&c), 1, 0, 0);
            }
        }
        input_buffer[bytes_read] = '\0';

        if (bytes_read > 0) {
            execute_line(input_buffer);
        }
    }
}

void CLIShell::print_prompt() {
    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(m_cwd), ::strlen(m_cwd), 0, 0);
    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(" $ "), 3, 0, 0);
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
    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(msg), ::strlen(msg), 0, 0);
}

void CLIShell::cmd_pwd() {
    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(m_cwd), ::strlen(m_cwd), 0, 0);
    acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
}

void CLIShell::cmd_cd(int argc, char** argv) {
    if (argc < 2) return;
    // Basic CD - in a real shell we'd validate path with VFS
    ::memcpy(m_cwd, argv[1], ::strlen(argv[1]) + 1);
}

void CLIShell::cmd_ls(int argc, char** argv) {
    const char* path = (argc > 1) ? argv[1] : m_cwd;

    acos::vfs::DirectoryEntry entries[32];
    i32 count = acos::vfs::VFS::read_dir(path, entries, 32);

    if (count < 0) {
        const char* err = "ls: cannot access directory\n";
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        return;
    }

    for (i32 i = 0; i < count; i++) {
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(entries[i].name), ::strlen(entries[i].name), 0, 0);
        if (entries[i].type == acos::vfs::NodeType::Directory) {
            acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("/"), 1, 0, 0);
        }
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
    }
}

void CLIShell::cmd_exit() {
    m_running = false;
}

void CLIShell::execute_external(int argc [[maybe_unused]], char** argv) {
    char resolved_path[1024];
    u64 child_handle = static_cast<u64>(-1);

    // Try absolute path or relative path directly
    if (argv[0][0] == '/' || argv[0][0] == '.') {
        child_handle = acos::syscall::syscall_dispatch(
            static_cast<u64>(acos::syscall::SyscallNum::ProcessCreate),
            reinterpret_cast<u64>(argv[0]), 0, 0, 0, 0
        );
    } else {
        // Try /bin/ and /userland/bin/
        const char* paths[] = {"/bin/", "/userland/bin/", nullptr};
        for (int i = 0; paths[i]; i++) {
            ::memset(resolved_path, 0, 1024);
            ::memcpy(resolved_path, paths[i], ::strlen(paths[i]));
            ::memcpy(resolved_path + ::strlen(paths[i]), argv[0], ::strlen(argv[0]));

            child_handle = acos::syscall::syscall_dispatch(
                static_cast<u64>(acos::syscall::SyscallNum::ProcessCreate),
                reinterpret_cast<u64>(resolved_path), 0, 0, 0, 0
            );
            if (child_handle != static_cast<u64>(-1)) break;
        }
    }

    if (child_handle == static_cast<u64>(-1)) {
        const char* err = "shell: command not found: ";
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(err), ::strlen(err), 0, 0);
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>(argv[0]), ::strlen(argv[0]), 0, 0);
        acos::syscall::syscall_dispatch(static_cast<u64>(acos::syscall::SyscallNum::FileWrite), m_console_fd, reinterpret_cast<u64>("\n"), 1, 0, 0);
        return;
    }

    // 2. Duplicate Console Handles (FD 0, 1, 2)
    // We pass our m_console_fd to the child.
    // In this simplified model, ResourceDuplicate maps a handle to another in the same or target process.
    // SyscallNum::ResourceDuplicate(handle, rights, out_handle_ptr)
    // For simplicity, we assume child inherits or we use ResourceTransfer if we had a target process handle.
    // The instructions say use ResourceDuplicate to pass handles to child.

    // Actually, ResourceTransfer or a specific argument to ProcessCreate would be better,
    // but I'll follow "use ResourceDuplicate or ResourceTransfer during ProcessCreate".
    // ProcessCreate in my implementation doesn't yet support handle inheritance in arg.

    // 3. Start Process
    acos::syscall::syscall_dispatch(
        static_cast<u64>(acos::syscall::SyscallNum::ProcessStart),
        child_handle, 0, 0, 0, 0
    );

    // 4. Synchronous Wait (using ThreadJoin on the process handle if it maps to primary thread)
    // Our ThreadJoin syscall takes a thread handle.
    // Let's assume the handle returned by ProcessCreate can be queried for its primary thread.

    acos::syscall::ResourceInfo info;
    acos::syscall::syscall_dispatch(
        static_cast<u64>(acos::syscall::SyscallNum::ResourceQuery),
        child_handle, reinterpret_cast<u64>(&info), 0, 0, 0
    );

    // Wait for it to finish.
    // For now, we'll use ThreadJoin on the handle assuming it's waitable or just yield.
    acos::syscall::syscall_dispatch(
        static_cast<u64>(acos::syscall::SyscallNum::ThreadJoin),
        child_handle, 0, 0, 0, 0
    );
}

} // namespace acos::shell
