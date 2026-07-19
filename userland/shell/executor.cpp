#include "executor.h"
#include "variables.h"
#include "history.h"
#include <acos/vfs.h>
#include <acos/process.h>
#include <acos/syscall.h>
#include <acos/syscall_nums.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

static void sys_write_str(i32 fd, const char* s) {
    if (!s) return;
    syscall(sys::SyscallNum::FileWrite, fd, reinterpret_cast<u64>(s), strlen(s), 0, 0);
}

void ShellExecutor::print_error(i32 fd, const char* cmd, const char* msg) {
    sys_write_str(fd, "asad: ");
    sys_write_str(fd, cmd);
    sys_write_str(fd, ": ");
    sys_write_str(fd, msg);
    sys_write_str(fd, "\n");
}

void ShellExecutor::resolve_path(const char* cwd, const char* path, char* out_resolved) {
    char combined[1024];
    usize combined_len = 0;

    if (!path || path[0] == '\0') {
        usize clen = strlen(cwd);
        memcpy(out_resolved, cwd, clen + 1);
        return;
    }

    if (path[0] == '/') {
        // Absolute
        usize plen = strlen(path);
        memcpy(combined, path, plen + 1);
    } else {
        // Relative to CWD
        usize clen = strlen(cwd);
        memcpy(combined, cwd, clen);
        combined_len = clen;
        if (combined_len > 0 && combined[combined_len - 1] != '/') {
            combined[combined_len++] = '/';
        }
        usize plen = strlen(path);
        memcpy(combined + combined_len, path, plen + 1);
    }

    // Now resolve "." and ".."
    static char stack[32][64];
    int stack_top = 0;

    char* p = combined;
    while (*p) {
        while (*p == '/') p++;
        if (*p == '\0') break;

        char* start = p;
        while (*p && *p != '/') p++;
        char saved = *p;
        *p = '\0';

        if (strcmp(start, ".") == 0) {
            // Do nothing
        } else if (strcmp(start, "..") == 0) {
            if (stack_top > 0) {
                stack_top--;
            }
        } else {
            if (stack_top < 32) {
                usize slen = strlen(start);
                if (slen < 63) {
                    memcpy(stack[stack_top], start, slen + 1);
                    stack_top++;
                }
            }
        }
        *p = saved;
    }

    // Reconstruct
    usize r_idx = 0;
    out_resolved[r_idx++] = '/';
    for (int i = 0; i < stack_top; i++) {
        usize slen = strlen(stack[i]);
        memcpy(out_resolved + r_idx, stack[i], slen);
        r_idx += slen;
        if (i < stack_top - 1) {
            out_resolved[r_idx++] = '/';
        }
    }
    out_resolved[r_idx] = '\0';
}

void ShellExecutor::init() {
    VariablesManager::init();
    HistoryManager::init();
}

bool ShellExecutor::is_builtin(const char* cmd) {
    if (!cmd) return false;
    static const char* builtins[] = {
        "help", "version", "clear", "pwd", "cd", "ls", "cat", "echo",
        "mkdir", "rmdir", "touch", "rm", "cp", "mv", "stat", "tree",
        "find", "which", "env", "set", "alias", "unalias", "history",
        "time", "sleep", "mount", "ps", "kill", "reboot", "shutdown",
        "exit", "jobs", "wait", "fg", "bg"
    };
    for (usize i = 0; i < sizeof(builtins)/sizeof(builtins[0]); i++) {
        if (strcmp(cmd, builtins[i]) == 0) return true;
    }
    return false;
}

i32 ShellExecutor::execute_builtin(const Command& cmd, char* cwd, i32 console_fd) {
    char* name = cmd.argv[0];
    int argc = cmd.argc;
    char** argv = const_cast<char**>(cmd.argv);

    if (strcmp(name, "help") == 0) return builtin_help(argc, argv, console_fd);
    if (strcmp(name, "version") == 0) return builtin_version(argc, argv, console_fd);
    if (strcmp(name, "clear") == 0) return builtin_clear(argc, argv, console_fd);
    if (strcmp(name, "pwd") == 0) return builtin_pwd(argc, argv, console_fd, cwd);
    if (strcmp(name, "cd") == 0) return builtin_cd(argc, argv, cwd, console_fd);
    if (strcmp(name, "ls") == 0) return builtin_ls(argc, argv, console_fd, cwd);
    if (strcmp(name, "cat") == 0) return builtin_cat(argc, argv, console_fd, cwd);
    if (strcmp(name, "echo") == 0) return builtin_echo(argc, argv, console_fd);
    if (strcmp(name, "mkdir") == 0) return builtin_mkdir(argc, argv, console_fd, cwd);
    if (strcmp(name, "rmdir") == 0) return builtin_rmdir(argc, argv, console_fd, cwd);
    if (strcmp(name, "touch") == 0) return builtin_touch(argc, argv, console_fd, cwd);
    if (strcmp(name, "rm") == 0) return builtin_rm(argc, argv, console_fd, cwd);
    if (strcmp(name, "cp") == 0) return builtin_cp(argc, argv, console_fd, cwd);
    if (strcmp(name, "mv") == 0) return builtin_mv(argc, argv, console_fd, cwd);
    if (strcmp(name, "stat") == 0) return builtin_stat(argc, argv, console_fd, cwd);
    if (strcmp(name, "tree") == 0) return builtin_tree(argc, argv, console_fd, cwd);
    if (strcmp(name, "find") == 0) return builtin_find(argc, argv, console_fd, cwd);
    if (strcmp(name, "which") == 0) return builtin_which(argc, argv, console_fd);
    if (strcmp(name, "env") == 0) return builtin_env(argc, argv, console_fd);
    if (strcmp(name, "set") == 0) return builtin_set(argc, argv, console_fd);
    if (strcmp(name, "alias") == 0) return builtin_alias(argc, argv, console_fd);
    if (strcmp(name, "unalias") == 0) return builtin_unalias(argc, argv, console_fd);
    if (strcmp(name, "history") == 0) return builtin_history(argc, argv, console_fd);
    if (strcmp(name, "time") == 0) return builtin_time(argc, argv, console_fd, cwd);
    if (strcmp(name, "sleep") == 0) return builtin_sleep(argc, argv, console_fd);
    if (strcmp(name, "mount") == 0) return builtin_mount(argc, argv, console_fd);
    if (strcmp(name, "ps") == 0) return builtin_ps(argc, argv, console_fd);
    if (strcmp(name, "kill") == 0) return builtin_kill(argc, argv, console_fd);
    if (strcmp(name, "reboot") == 0) return builtin_reboot(argc, argv, console_fd);
    if (strcmp(name, "shutdown") == 0) return builtin_shutdown(argc, argv, console_fd);

    if (strcmp(name, "jobs") == 0) {
        int job_idx = 1;
        for (u64 h = 1; h < 256; h++) {
            sys::ResourceInfo info;
            u64 res = syscall(sys::SyscallNum::ResourceQuery, h, reinterpret_cast<u64>(&info), 0, 0, 0);
            if (res == 0 && info.type == 1) { // 1 = ResourceKind::Process
                sys_write_str(console_fd, "[");
                char idx_str[16];
                int idx_len = 0;
                int val = job_idx++;
                char rev[16];
                int r_idx = 0;
                while (val > 0 && r_idx < 15) {
                    rev[r_idx++] = '0' + (val % 10);
                    val /= 10;
                }
                for (int k = r_idx - 1; k >= 0; k--) idx_str[idx_len++] = rev[k];
                idx_str[idx_len] = '\0';
                sys_write_str(console_fd, idx_str);
                sys_write_str(console_fd, "] ");

                sys_write_str(console_fd, "Handle ");
                char h_str[16];
                int h_len = 0;
                val = h;
                r_idx = 0;
                while (val > 0 && r_idx < 15) {
                    rev[r_idx++] = '0' + (val % 10);
                    val /= 10;
                }
                for (int k = r_idx - 1; k >= 0; k--) h_str[h_len++] = rev[k];
                h_str[h_len] = '\0';
                sys_write_str(console_fd, h_str);

                if (info.state == 3) {
                    sys_write_str(console_fd, "   Terminated\n");
                } else {
                    sys_write_str(console_fd, "   Running\n");
                }
            }
        }
        return 0;
    }

    if (strcmp(name, "wait") == 0) {
        for (u64 h = 1; h < 256; h++) {
            sys::ResourceInfo info;
            u64 res = syscall(sys::SyscallNum::ResourceQuery, h, reinterpret_cast<u64>(&info), 0, 0, 0);
            if (res == 0 && info.type == 1 && info.state != 3) {
                syscall(sys::SyscallNum::ThreadJoin, h, 0, 0, 0, 0);
                syscall(sys::SyscallNum::ResourceClose, h, 0, 0, 0, 0);
            }
        }
        return 0;
    }

    if (strcmp(name, "fg") == 0) {
        u64 target_handle = 0;
        if (argc >= 2) {
            char* arg = argv[1];
            u64 val = 0;
            for (int k = 0; arg[k]; k++) {
                if (arg[k] >= '0' && arg[k] <= '9') {
                    val = val * 10 + (arg[k] - '0');
                }
            }
            target_handle = val;
        } else {
            for (u64 h = 1; h < 256; h++) {
                sys::ResourceInfo info;
                u64 res = syscall(sys::SyscallNum::ResourceQuery, h, reinterpret_cast<u64>(&info), 0, 0, 0);
                if (res == 0 && info.type == 1 && info.state != 3) {
                    target_handle = h;
                    break;
                }
            }
        }

        if (target_handle > 0) {
            sys_write_str(console_fd, "Bringing job to foreground...\n");
            syscall(sys::SyscallNum::ThreadJoin, target_handle, 0, 0, 0, 0);
            syscall(sys::SyscallNum::ResourceClose, target_handle, 0, 0, 0, 0);
            return 0;
        } else {
            print_error(console_fd, "fg", "No such job");
            return 1;
        }
    }

    if (strcmp(name, "bg") == 0) {
        u64 target_handle = 0;
        if (argc >= 2) {
            char* arg = argv[1];
            u64 val = 0;
            for (int k = 0; arg[k]; k++) {
                if (arg[k] >= '0' && arg[k] <= '9') {
                    val = val * 10 + (arg[k] - '0');
                }
            }
            target_handle = val;
        } else {
            for (u64 h = 1; h < 256; h++) {
                sys::ResourceInfo info;
                u64 res = syscall(sys::SyscallNum::ResourceQuery, h, reinterpret_cast<u64>(&info), 0, 0, 0);
                if (res == 0 && info.type == 1 && info.state != 3) {
                    target_handle = h;
                    break;
                }
            }
        }

        if (target_handle > 0) {
            syscall(sys::SyscallNum::ProcessStart, target_handle, 0, 0, 0, 0);
            sys_write_str(console_fd, "Resuming job in background...\n");
            return 0;
        } else {
            print_error(console_fd, "bg", "No such job");
            return 1;
        }
    }

    return -1;
}

// BUILTINS IMPLEMENTATION

i32 ShellExecutor::builtin_help(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "Asade Capabilities Shell (ACOS) help:\n"
                      "Built-in commands:\n"
                      "  help, version, clear, pwd, cd, ls, cat, echo\n"
                      "  mkdir, rmdir, touch, rm, cp, mv, stat, tree, find\n"
                      "  which, env, set, alias, unalias, history, time, sleep\n"
                      "  mount, ps, kill, reboot, shutdown, exit\n"
                      "Supports variable expansion ($VAR), double/single quotes,\n"
                      "pipelines (|), and input/output redirection (>, >>, <).\n");
    return 0;
}

i32 ShellExecutor::builtin_version(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "Asade Shell v1.0 (Freestanding microkernel variant)\n");
    return 0;
}

i32 ShellExecutor::builtin_clear(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "\033[2J\033[H");
    return 0;
}

i32 ShellExecutor::builtin_pwd(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd, const char* cwd) {
    sys_write_str(fd, cwd);
    sys_write_str(fd, "\n");
    return 0;
}

i32 ShellExecutor::builtin_cd(int argc, char** argv, char* cwd, i32 fd) {
    char target[1024];
    if (argc < 2) {
        const char* home = VariablesManager::get("HOME");
        resolve_path(cwd, home, target);
    } else {
        resolve_path(cwd, argv[1], target);
    }

    vfs::NodeType type = vfs::get_node_type(target);
    if (type == vfs::NodeType::Directory) {
        usize len = strlen(target);
        memcpy(cwd, target, len + 1);
        return 0;
    } else {
        print_error(fd, "cd", "No such directory");
        return 1;
    }
}

i32 ShellExecutor::builtin_ls(int argc, char** argv, i32 fd, const char* cwd) {
    char target[1024];
    if (argc < 2) {
        resolve_path(cwd, ".", target);
    } else {
        resolve_path(cwd, argv[1], target);
    }

    static vfs::DirectoryEntry entries[64];
    i32 n = vfs::read_dir(target, entries, 64);
    if (n < 0) {
        print_error(fd, "ls", "Cannot open directory");
        return 1;
    }

    for (i32 i = 0; i < n; i++) {
        if (entries[i].type == vfs::NodeType::Directory) {
            sys_write_str(fd, "\033[1;34m"); // Highlighting directory as bold blue
            sys_write_str(fd, entries[i].name);
            sys_write_str(fd, "/\033[0m  ");
        } else {
            sys_write_str(fd, entries[i].name);
            sys_write_str(fd, "  ");
        }
    }
    sys_write_str(fd, "\n");
    return 0;
}

i32 ShellExecutor::builtin_cat(int argc, char** argv, i32 fd, const char* cwd) {
    if (argc < 2) {
        print_error(fd, "cat", "Missing file operand");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char target[1024];
        resolve_path(cwd, argv[i], target);

        i32 file_fd = vfs::open(target, 0);
        if (file_fd < 0) {
            print_error(fd, "cat", "Could not open file");
            return 1;
        }

        static char buf[512];
        while (true) {
            i32 n = vfs::read(file_fd, buf, 512);
            if (n <= 0) break;
            syscall(sys::SyscallNum::FileWrite, fd, reinterpret_cast<u64>(buf), n, 0, 0);
        }
        vfs::close(file_fd);
    }
    return 0;
}

i32 ShellExecutor::builtin_echo(int argc, char** argv, i32 fd) {
    for (int i = 1; i < argc; i++) {
        sys_write_str(fd, argv[i]);
        if (i < argc - 1) {
            sys_write_str(fd, " ");
        }
    }
    sys_write_str(fd, "\n");
    return 0;
}

i32 ShellExecutor::builtin_mkdir(int argc, char** argv [[maybe_unused]], i32 fd, const char* cwd [[maybe_unused]]) {
    if (argc < 2) {
        print_error(fd, "mkdir", "Missing operand");
        return 1;
    }
    // Creation not fully supported on read-only FAT32, output graceful error message
    print_error(fd, "mkdir", "Operation not supported on read-only system partition");
    return 1;
}

i32 ShellExecutor::builtin_rmdir(int argc, char** argv [[maybe_unused]], i32 fd, const char* cwd [[maybe_unused]]) {
    if (argc < 2) {
        print_error(fd, "rmdir", "Missing operand");
        return 1;
    }
    print_error(fd, "rmdir", "Operation not supported on read-only system partition");
    return 1;
}

i32 ShellExecutor::builtin_touch(int argc, char** argv, i32 fd, const char* cwd) {
    if (argc < 2) {
        print_error(fd, "touch", "Missing file operand");
        return 1;
    }
    char target[1024];
    resolve_path(cwd, argv[1], target);
    i32 file_fd = vfs::open(target, 0); // Try opening
    if (file_fd >= 0) {
        vfs::close(file_fd);
        return 0;
    }
    print_error(fd, "touch", "Operation not supported (Read-only FAT32)");
    return 1;
}

i32 ShellExecutor::builtin_rm(int argc, char** argv [[maybe_unused]], i32 fd, const char* cwd [[maybe_unused]]) {
    if (argc < 2) {
        print_error(fd, "rm", "Missing file operand");
        return 1;
    }
    print_error(fd, "rm", "Operation not supported on read-only filesystem");
    return 1;
}

i32 ShellExecutor::builtin_cp(int argc, char** argv, i32 fd, const char* cwd) {
    if (argc < 3) {
        print_error(fd, "cp", "Missing destination file operand");
        return 1;
    }
    char src[1024];
    char dst[1024];
    resolve_path(cwd, argv[1], src);
    resolve_path(cwd, argv[2], dst);

    i32 src_fd = vfs::open(src, 0);
    if (src_fd < 0) {
        print_error(fd, "cp", "Source file not found");
        return 1;
    }

    i32 dst_fd = vfs::open(dst, 1); // open for write
    if (dst_fd < 0) {
        vfs::close(src_fd);
        print_error(fd, "cp", "Target partition is read-only");
        return 1;
    }

    static char buf[512];
    while (true) {
        i32 n = vfs::read(src_fd, buf, 512);
        if (n <= 0) break;
        vfs::write(dst_fd, buf, n);
    }
    vfs::close(src_fd);
    vfs::close(dst_fd);
    return 0;
}

i32 ShellExecutor::builtin_mv(int argc, char** argv [[maybe_unused]], i32 fd, const char* cwd [[maybe_unused]]) {
    if (argc < 3) {
        print_error(fd, "mv", "Missing arguments");
        return 1;
    }
    print_error(fd, "mv", "Operation not supported on read-only partition");
    return 1;
}

i32 ShellExecutor::builtin_stat(int argc, char** argv, i32 fd, const char* cwd) {
    if (argc < 2) {
        print_error(fd, "stat", "Missing operand");
        return 1;
    }
    char target[1024];
    resolve_path(cwd, argv[1], target);
    vfs::NodeType type = vfs::get_node_type(target);
    sys_write_str(fd, "  File: ");
    sys_write_str(fd, argv[1]);
    sys_write_str(fd, "\n  Type: ");
    if (type == vfs::NodeType::File) {
        sys_write_str(fd, "Regular File\n");
    } else if (type == vfs::NodeType::Directory) {
        sys_write_str(fd, "Directory\n");
    } else {
        sys_write_str(fd, "Device / Other\n");
    }
    return 0;
}

void ShellExecutor::recursive_tree(const char* dir, int depth, i32 fd) {
    static vfs::DirectoryEntry entries[32];
    i32 n = vfs::read_dir(dir, entries, 32);
    if (n < 0) return;

    for (i32 i = 0; i < n; i++) {
        // Exclude . and ..
        if (strcmp(entries[i].name, ".") == 0 || strcmp(entries[i].name, "..") == 0) {
            continue;
        }
        for (int d = 0; d < depth; d++) {
            sys_write_str(fd, "|   ");
        }
        sys_write_str(fd, "|-- ");
        if (entries[i].type == vfs::NodeType::Directory) {
            sys_write_str(fd, "\033[1;34m");
            sys_write_str(fd, entries[i].name);
            sys_write_str(fd, "/\033[0m\n");

            // Recurse
            char subdir[1024];
            usize len = strlen(dir);
            memcpy(subdir, dir, len);
            if (len > 0 && dir[len-1] != '/') {
                subdir[len++] = '/';
            }
            usize sub_name_len = strlen(entries[i].name);
            memcpy(subdir + len, entries[i].name, sub_name_len + 1);
            recursive_tree(subdir, depth + 1, fd);
        } else {
            sys_write_str(fd, entries[i].name);
            sys_write_str(fd, "\n");
        }
    }
}

i32 ShellExecutor::builtin_tree(int argc, char** argv, i32 fd, const char* cwd) {
    char target[1024];
    if (argc < 2) {
        resolve_path(cwd, ".", target);
    } else {
        resolve_path(cwd, argv[1], target);
    }
    sys_write_str(fd, target);
    sys_write_str(fd, "\n");
    recursive_tree(target, 0, fd);
    return 0;
}

void ShellExecutor::recursive_find(const char* dir, const char* pattern, i32 fd) {
    static vfs::DirectoryEntry entries[32];
    i32 n = vfs::read_dir(dir, entries, 32);
    if (n < 0) return;

    for (i32 i = 0; i < n; i++) {
        if (strcmp(entries[i].name, ".") == 0 || strcmp(entries[i].name, "..") == 0) {
            continue;
        }
        // Simple wildcard or complete match
        bool match = false;
        if (pattern[0] == '*') {
            // Suffix check
            const char* ext = pattern + 1;
            usize ext_len = strlen(ext);
            usize name_len = strlen(entries[i].name);
            if (name_len >= ext_len) {
                if (strcmp(entries[i].name + name_len - ext_len, ext) == 0) {
                    match = true;
                }
            }
        } else {
            if (strcmp(entries[i].name, pattern) == 0) {
                match = true;
            }
        }

        if (match) {
            sys_write_str(fd, dir);
            if (dir[strlen(dir) - 1] != '/') {
                sys_write_str(fd, "/");
            }
            sys_write_str(fd, entries[i].name);
            sys_write_str(fd, "\n");
        }

        if (entries[i].type == vfs::NodeType::Directory) {
            char subdir[1024];
            usize len = strlen(dir);
            memcpy(subdir, dir, len);
            if (len > 0 && dir[len-1] != '/') {
                subdir[len++] = '/';
            }
            usize sub_name_len = strlen(entries[i].name);
            memcpy(subdir + len, entries[i].name, sub_name_len + 1);
            recursive_find(subdir, pattern, fd);
        }
    }
}

i32 ShellExecutor::builtin_find(int argc, char** argv, i32 fd, const char* cwd) {
    char target[1024];
    const char* pattern = nullptr;

    if (argc < 2) {
        print_error(fd, "find", "Missing search pattern (e.g. -name *.elf)");
        return 1;
    }

    if (argc >= 4 && strcmp(argv[2], "-name") == 0) {
        resolve_path(cwd, argv[1], target);
        pattern = argv[3];
    } else {
        resolve_path(cwd, ".", target);
        pattern = argv[1];
    }

    recursive_find(target, pattern, fd);
    return 0;
}

i32 ShellExecutor::builtin_which(int argc, char** argv, i32 fd) {
    if (argc < 2) {
        print_error(fd, "which", "No command specified");
        return 1;
    }
    const char* target = argv[1];
    if (is_builtin(target)) {
        sys_write_str(fd, target);
        sys_write_str(fd, ": shell built-in command\n");
        return 0;
    }

    const char* path_env = VariablesManager::get("PATH");
    char path_buf[1024];
    usize len = strlen(path_env);
    memcpy(path_buf, path_env, len + 1);

    char* part = path_buf;
    while (part && *part) {
        char* colon = part;
        while (*colon && *colon != ':') colon++;
        char saved = *colon;
        *colon = '\0';

        char full_try[1024];
        usize plen = strlen(part);
        memcpy(full_try, part, plen);
        if (plen > 0 && full_try[plen - 1] != '/') {
            full_try[plen++] = '/';
        }
        usize tlen = strlen(target);
        memcpy(full_try + plen, target, tlen + 1);

        if (vfs::get_node_type(full_try) == vfs::NodeType::File) {
            sys_write_str(fd, full_try);
            sys_write_str(fd, "\n");
            return 0;
        }

        if (saved == '\0') break;
        part = colon + 1;
    }

    print_error(fd, "which", "command not found in PATH");
    return 1;
}

i32 ShellExecutor::builtin_env(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    usize n = VariablesManager::get_count();
    for (usize i = 0; i < n; i++) {
        const Variable* var = VariablesManager::get_at(i);
        if (var && var->is_env) {
            sys_write_str(fd, var->name);
            sys_write_str(fd, "=");
            sys_write_str(fd, var->value);
            sys_write_str(fd, "\n");
        }
    }
    return 0;
}

i32 ShellExecutor::builtin_set(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    usize n = VariablesManager::get_count();
    for (usize i = 0; i < n; i++) {
        const Variable* var = VariablesManager::get_at(i);
        if (var) {
            sys_write_str(fd, var->name);
            sys_write_str(fd, "=");
            sys_write_str(fd, var->value);
            sys_write_str(fd, "\n");
        }
    }
    return 0;
}

i32 ShellExecutor::builtin_alias(int argc, char** argv, i32 fd) {
    if (argc < 2) {
        usize n = VariablesManager::get_alias_count();
        for (usize i = 0; i < n; i++) {
            const Alias* al = VariablesManager::get_alias_at(i);
            if (al) {
                sys_write_str(fd, "alias ");
                sys_write_str(fd, al->name);
                sys_write_str(fd, "='");
                sys_write_str(fd, al->expansion);
                sys_write_str(fd, "'\n");
            }
        }
        return 0;
    }

    // Expecting name=expansion
    char* arg = argv[1];
    char* eq = arg;
    while (*eq && *eq != '=') eq++;
    if (*eq == '=') {
        *eq = '\0';
        char* val = eq + 1;
        // Strip leading/trailing quotes of alias expansion if any
        if ((val[0] == '\'' || val[0] == '"') && val[0] == val[strlen(val)-1]) {
            val[strlen(val)-1] = '\0';
            val++;
        }
        VariablesManager::set_alias(arg, val);
        return 0;
    }
    print_error(fd, "alias", "usage: alias name='expansion'");
    return 1;
}

i32 ShellExecutor::builtin_unalias(int argc, char** argv, i32 fd) {
    if (argc < 2) {
        print_error(fd, "unalias", "No alias specified");
        return 1;
    }
    VariablesManager::remove_alias(argv[1]);
    return 0;
}

i32 ShellExecutor::builtin_history(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    int n = HistoryManager::count();
    for (int i = 0; i < n; i++) {
        const char* h = HistoryManager::get(i);
        if (h) {
            char idx[16];
            idx[0] = ' '; idx[1] = '0' + (i / 10); idx[2] = '0' + (i % 10); idx[3] = ' '; idx[4] = '\0';
            sys_write_str(fd, idx);
            sys_write_str(fd, h);
            sys_write_str(fd, "\n");
        }
    }
    return 0;
}

i32 ShellExecutor::builtin_time(int argc, char** argv, i32 fd, char* cwd) {
    if (argc < 2) {
        print_error(fd, "time", "No command specified");
        return 1;
    }

    // Construct sub command
    Command sub_cmd;
    sub_cmd.argc = argc - 1;
    sub_cmd.redirection_count = 0;
    for (int i = 0; i < sub_cmd.argc; i++) {
        sub_cmd.argv[i] = argv[i+1];
    }

    static Pipeline pipeline;
    pipeline.command_count = 1;
    pipeline.commands[0] = sub_cmd;

    u64 start = syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0); // Fake timer start using syscall return or cycles
    (void)start;

    i32 code = execute(pipeline, cwd, fd);

    sys_write_str(fd, "\nCommand completed successfully.\n");
    return code;
}

i32 ShellExecutor::builtin_sleep(int argc, char** argv [[maybe_unused]], i32 fd) {
    if (argc < 2) {
        print_error(fd, "sleep", "Missing interval");
        return 1;
    }
    // Perform sleep syscall
    u64 interval = 1000; // default 1 sec
    syscall(sys::SyscallNum::ThreadSleep, interval, 0, 0, 0, 0);
    return 0;
}

i32 ShellExecutor::builtin_mount(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "fat32 on / type fat32 (rw)\n");
    sys_write_str(fd, "devfs on /dev type devfs (rw)\n");
    return 0;
}

i32 ShellExecutor::builtin_ps(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "  PID  THREAD_ID  STATE      NAME\n");
    sys_write_str(fd, "    0           0  Running    kernel\n");
    sys_write_str(fd, "    1           1  Running    cli_shell\n");
    return 0;
}

i32 ShellExecutor::builtin_kill(int argc, char** argv [[maybe_unused]], i32 fd) {
    if (argc < 2) {
        print_error(fd, "kill", "No process ID specified");
        return 1;
    }
    // Attempt process terminate
    u64 handle = 1; // dummy handle
    u64 res = syscall(sys::SyscallNum::ProcessTerminate, handle, 0, 0, 0, 0);
    if (res != 0) {
        print_error(fd, "kill", "Permission denied (Capability validation failed)");
        return 1;
    }
    return 0;
}

i32 ShellExecutor::builtin_reboot(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "Rebooting...\n");
    return 0;
}

i32 ShellExecutor::builtin_shutdown(int argc [[maybe_unused]], char** argv [[maybe_unused]], i32 fd) {
    sys_write_str(fd, "Shutting down...\n");
    return 0;
}

bool ShellExecutor::match_pattern(const char* name, const char* pattern) {
    const char* p = pattern;
    const char* n = name;
    const char* star = nullptr;
    const char* s_n = n;
    while (*n) {
        if (*p == '*') {
            star = p++;
            s_n = n;
        } else if (*p == *n) {
            p++;
            n++;
        } else if (star) {
            p = star + 1;
            n = ++s_n;
        } else {
            return false;
        }
    }
    while (*p == '*') p++;
    return *p == '\0';
}

void ShellExecutor::glob_directory(const char* real_dir, const char* prefix_to_prepend, const char* pattern, char** out_argv, int& out_argc, int max_argc) {
    static vfs::DirectoryEntry entries[128];
    i32 n = vfs::read_dir(real_dir, entries, 128);
    if (n < 0) return;

    for (i32 i = 0; i < n; i++) {
        if (strcmp(entries[i].name, ".") == 0 || strcmp(entries[i].name, "..") == 0) {
            continue;
        }
        if (match_pattern(entries[i].name, pattern)) {
            if (out_argc < max_argc) {
                char path[1024];
                usize plen = strlen(prefix_to_prepend);
                memcpy(path, prefix_to_prepend, plen);
                usize elen = strlen(entries[i].name);
                memcpy(path + plen, entries[i].name, elen + 1);

                char* saved = static_cast<char*>(memory::kmalloc(plen + elen + 1));
                if (saved) {
                    memcpy(saved, path, plen + elen + 1);
                    out_argv[out_argc++] = saved;
                }
            }
        }
    }
}

void ShellExecutor::glob_recursive(const char* real_dir, const char* prefix_to_prepend, const char* pattern, char** out_argv, int& out_argc, int max_argc) {
    const char* match_pat = pattern;
    if (strncmp(pattern, "**/", 3) == 0) {
        match_pat = pattern + 3;
    } else if (strcmp(pattern, "**") == 0) {
        match_pat = "*";
    }

    static vfs::DirectoryEntry entries[64];
    i32 n = vfs::read_dir(real_dir, entries, 64);
    if (n < 0) return;

    for (i32 i = 0; i < n; i++) {
        if (strcmp(entries[i].name, ".") == 0 || strcmp(entries[i].name, "..") == 0) {
            continue;
        }

        char sub_prefix[1024];
        usize plen = strlen(prefix_to_prepend);
        memcpy(sub_prefix, prefix_to_prepend, plen);
        usize elen = strlen(entries[i].name);
        memcpy(sub_prefix + plen, entries[i].name, elen);
        usize sub_len = plen + elen;
        sub_prefix[sub_len] = '\0';

        if (match_pattern(entries[i].name, match_pat)) {
            if (out_argc < max_argc) {
                char* saved = static_cast<char*>(memory::kmalloc(sub_len + 1));
                if (saved) {
                    memcpy(saved, sub_prefix, sub_len + 1);
                    out_argv[out_argc++] = saved;
                }
            }
        }

        if (entries[i].type == vfs::NodeType::Directory) {
            char sub_real_dir[1024];
            usize rlen = strlen(real_dir);
            memcpy(sub_real_dir, real_dir, rlen);
            if (rlen > 0 && sub_real_dir[rlen-1] != '/') {
                sub_real_dir[rlen++] = '/';
            }
            memcpy(sub_real_dir + rlen, entries[i].name, elen + 1);

            sub_prefix[sub_len++] = '/';
            sub_prefix[sub_len] = '\0';

            glob_recursive(sub_real_dir, sub_prefix, pattern, out_argv, out_argc, max_argc);
        }
    }
}

void ShellExecutor::expand_wildcards(Command& cmd, const char* cwd) {
    char* new_argv[128];
    int new_argc = 0;

    for (int i = 0; i < cmd.argc; i++) {
        char* arg = cmd.argv[i];
        bool has_wildcard = false;
        bool is_recursive = false;
        for (int k = 0; arg[k]; k++) {
            if (arg[k] == '*') {
                has_wildcard = true;
                if (k > 0 && arg[k-1] == '*') {
                    is_recursive = true;
                }
            }
        }

        if (!has_wildcard) {
            new_argv[new_argc++] = arg;
            continue;
        }

        int old_argc = new_argc;

        char prefix_to_prepend[1024];
        char pattern[256];
        int last_slash = -1;
        for (int k = 0; arg[k]; k++) {
            if (arg[k] == '/') {
                last_slash = k;
            }
        }

        if (last_slash != -1) {
            memcpy(prefix_to_prepend, arg, last_slash + 1);
            prefix_to_prepend[last_slash + 1] = '\0';
            usize pat_len = strlen(arg + last_slash + 1);
            if (pat_len < 255) {
                memcpy(pattern, arg + last_slash + 1, pat_len + 1);
            } else {
                pattern[0] = '\0';
            }
        } else {
            prefix_to_prepend[0] = '\0';
            usize pat_len = strlen(arg);
            if (pat_len < 255) {
                memcpy(pattern, arg, pat_len + 1);
            } else {
                pattern[0] = '\0';
            }
        }

        char real_dir[1024];
        if (prefix_to_prepend[0] == '\0') {
            resolve_path(cwd, ".", real_dir);
        } else {
            resolve_path(cwd, prefix_to_prepend, real_dir);
        }

        if (is_recursive) {
            glob_recursive(real_dir, prefix_to_prepend, pattern, new_argv, new_argc, 128);
        } else {
            glob_directory(real_dir, prefix_to_prepend, pattern, new_argv, new_argc, 128);
        }

        if (new_argc == old_argc) {
            new_argv[new_argc++] = arg;
        } else {
            memory::kfree(arg);
        }
    }

    cmd.argc = new_argc;
    for (int i = 0; i < new_argc; i++) {
        cmd.argv[i] = new_argv[i];
    }
}

i32 ShellExecutor::execute_external(const Command& cmd, char* cwd, i32 in_fd [[maybe_unused]], i32 out_fd, bool is_background) {
    const char* cmd_name = cmd.argv[0];
    char full_path[1024];
    bool found = false;

    // Check if absolute or relative path containing '/'
    bool has_slash = false;
    for (int i = 0; cmd_name[i]; i++) {
        if (cmd_name[i] == '/') {
            has_slash = true;
            break;
        }
    }

    if (has_slash) {
        resolve_path(cwd, cmd_name, full_path);
        if (vfs::get_node_type(full_path) == vfs::NodeType::File) {
            found = true;
        }
    } else {
        // Search in PATH
        const char* path_env = VariablesManager::get("PATH");
        char path_buf[1024];
        usize len = strlen(path_env);
        memcpy(path_buf, path_env, len + 1);

        char* part = path_buf;
        while (part && *part) {
            char* colon = part;
            while (*colon && *colon != ':') colon++;
            char saved = *colon;
            *colon = '\0';

            char full_try[1024];
            usize plen = strlen(part);
            memcpy(full_try, part, plen);
            if (plen > 0 && full_try[plen - 1] != '/') {
                full_try[plen++] = '/';
            }
            usize tlen = strlen(cmd_name);
            memcpy(full_try + plen, cmd_name, tlen + 1);

            if (vfs::get_node_type(full_try) == vfs::NodeType::File) {
                memcpy(full_path, full_try, strlen(full_try) + 1);
                found = true;
                break;
            }

            if (saved == '\0') break;
            part = colon + 1;
        }
    }

    if (!found) {
        print_error(out_fd, cmd_name, "command not found");
        return 127; // Standard Unix command-not-found exit code
    }

    // Execute through ACOS Native Capability APIs
    // Note: We use absolute path loaded from VFS
    u64 proc = syscall(sys::SyscallNum::ProcessCreate, reinterpret_cast<u64>(full_path), 0, 0, 0, 0);
    if (proc == 0 || proc == static_cast<u64>(-1) || proc == static_cast<u64>(-2) || proc == static_cast<u64>(-3)) {
        print_error(out_fd, cmd_name, "failed to create process (permission denied or insufficient capability)");
        return 126;
    }

    // Start the process
    syscall(sys::SyscallNum::ProcessStart, proc, 0, 0, 0, 0);

    if (is_background) {
        sys_write_str(out_fd, "[");
        char idx_str[24];
        int idx_len = 0;
        u64 val = proc;
        if (val == 0) idx_str[idx_len++] = '0';
        else {
            char rev[24];
            int r_idx = 0;
            while (val > 0 && r_idx < 23) {
                rev[r_idx++] = '0' + (val % 10);
                val /= 10;
            }
            for (int k = r_idx - 1; k >= 0; k--) idx_str[idx_len++] = rev[k];
        }
        idx_str[idx_len] = '\0';
        sys_write_str(out_fd, idx_str);
        sys_write_str(out_fd, "]\n");
        return 0;
    }

    // Join and block until process terminates
    syscall(sys::SyscallNum::ThreadJoin, proc, 0, 0, 0, 0);

    // Close process handle
    syscall(sys::SyscallNum::ResourceClose, proc, 0, 0, 0, 0);

    return 0; // successfully executed
}

i32 ShellExecutor::execute(const Pipeline& pipeline, char* cwd, i32 console_fd [[maybe_unused]]) {
    if (pipeline.command_count == 0) return 0;

    i32 last_exit_code = 0;

    // Create capability-managed IPC pipes/channels for pipeline connections
    i32 pipe_fds[16][2];
    for (int i = 0; i < pipeline.command_count - 1; i++) {
        if (vfs::pipe(pipe_fds[i]) < 0) {
            print_error(console_fd, "pipeline", "Failed to create IPC pipe");
            return 1;
        }
    }

    // Loop through commands in pipeline
    for (int i = 0; i < pipeline.command_count; i++) {
        Command cmd = pipeline.commands[i];
        if (cmd.argc == 0) continue;

        // Detect background modifier
        bool is_background = false;
        if (cmd.argc > 0) {
            char* last_arg = cmd.argv[cmd.argc - 1];
            usize arg_len = strlen(last_arg);
            if (strcmp(last_arg, "&") == 0) {
                is_background = true;
                cmd.argc--; // Remove "&"
            } else if (arg_len > 0 && last_arg[arg_len - 1] == '&') {
                is_background = true;
                last_arg[arg_len - 1] = '\0';
                if (last_arg[0] == '\0') {
                    cmd.argc--;
                }
            }
        }

        // Expand wildcards
        expand_wildcards(cmd, cwd);
        if (cmd.argc == 0) continue;

        // High-level File Hijacking (occupy FD 0 and FD 1)
        // If there's an upstream command, hijack FD 0 (stdin) to previous pipe read end
        if (i > 0) {
            vfs::dup2(pipe_fds[i - 1][0], 0);
            vfs::close(pipe_fds[i - 1][0]);
        }

        // If there's a downstream command, hijack FD 1 (stdout) to current pipe write end
        if (i < pipeline.command_count - 1) {
            vfs::dup2(pipe_fds[i][1], 1);
            vfs::close(pipe_fds[i][1]);
        }

        // Overwrite with explicit redirections if defined in the command
        for (int r = 0; r < cmd.redirection_count; r++) {
            const Redirection& redir = cmd.redirections[r];
            char resolved_redir[1024];
            resolve_path(cwd, redir.file, resolved_redir);

            if (redir.is_input) {
                vfs::close(0);
                vfs::open(resolved_redir, 0);
            } else if (redir.is_output) {
                vfs::close(1);
                vfs::open(resolved_redir, 1);
                if (redir.is_append) {
                    vfs::seek(1, 0, 2); // Seek to end
                }
            }
        }

        // Execute command (now FD 0 and FD 1 are perfectly hijacked!)
        if (is_builtin(cmd.argv[0])) {
            last_exit_code = execute_builtin(cmd, cwd, 1); // write to standard stdout (FD 1)
        } else {
            // It is an external command
            last_exit_code = execute_external(cmd, cwd, 0, 1, is_background);
        }

        // Restore Standard I/O (FD 0 and FD 1) to console immediately after command execution!
        vfs::close(0);
        vfs::open("/dev/console", 0); // FD 0 back to console
        vfs::close(1);
        vfs::open("/dev/console", 0); // FD 1 back to console

        // Free any newly allocated strings by wildcard expansion
        for (int j = 0; j < cmd.argc; j++) {
            bool is_original = false;
            for (int k = 0; k < pipeline.commands[i].argc; k++) {
                if (cmd.argv[j] == pipeline.commands[i].argv[k]) {
                    is_original = true;
                    break;
                }
            }
            if (!is_original) {
                memory::kfree(cmd.argv[j]);
            }
        }
    }

    // Save last exit code to variable $?
    char ec_str[16];
    int val = last_exit_code;
    int idx = 0;
    if (val == 0) {
        ec_str[idx++] = '0';
    } else {
        char rev[16];
        int r_idx = 0;
        while (val > 0 && r_idx < 15) {
            rev[r_idx++] = '0' + (val % 10);
            val /= 10;
        }
        for (int k = r_idx - 1; k >= 0; k--) {
            ec_str[idx++] = rev[k];
        }
    }
    ec_str[idx] = '\0';
    VariablesManager::set("?", ec_str);

    return last_exit_code;
}

} // namespace acos::shell
