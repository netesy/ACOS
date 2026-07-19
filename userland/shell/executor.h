#pragma once
#include <acos/types.h>
#include "parser.h"

namespace acos::shell {

class ShellExecutor {
public:
    static void init();
    static i32 execute(const Pipeline& pipeline, char* cwd, i32 console_fd);

private:
    // Built-ins execution
    static bool is_builtin(const char* cmd);
    static i32 execute_builtin(const Command& cmd, char* cwd, i32 console_fd);

    // Individual Built-ins
    static i32 builtin_help(int argc, char** argv, i32 fd);
    static i32 builtin_version(int argc, char** argv, i32 fd);
    static i32 builtin_clear(int argc, char** argv, i32 fd);
    static i32 builtin_pwd(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_cd(int argc, char** argv, char* cwd, i32 fd);
    static i32 builtin_ls(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_cat(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_echo(int argc, char** argv, i32 fd);
    static i32 builtin_mkdir(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_rmdir(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_touch(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_rm(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_cp(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_mv(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_stat(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_tree(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_find(int argc, char** argv, i32 fd, const char* cwd);
    static i32 builtin_which(int argc, char** argv, i32 fd);
    static i32 builtin_env(int argc, char** argv, i32 fd);
    static i32 builtin_set(int argc, char** argv, i32 fd);
    static i32 builtin_alias(int argc, char** argv, i32 fd);
    static i32 builtin_unalias(int argc, char** argv, i32 fd);
    static i32 builtin_history(int argc, char** argv, i32 fd);
    static i32 builtin_time(int argc, char** argv, i32 fd, char* cwd);
    static i32 builtin_sleep(int argc, char** argv, i32 fd);
    static i32 builtin_mount(int argc, char** argv, i32 fd);
    static i32 builtin_ps(int argc, char** argv, i32 fd);
    static i32 builtin_kill(int argc, char** argv, i32 fd);
    static i32 builtin_reboot(int argc, char** argv, i32 fd);
    static i32 builtin_shutdown(int argc, char** argv, i32 fd);

    static i32 execute_external(const Command& cmd, char* cwd, i32 in_fd, i32 out_fd);

    // Helpers
    static void resolve_path(const char* cwd, const char* path, char* out_resolved);
    static void print_error(i32 fd, const char* cmd, const char* msg);
    static void recursive_tree(const char* dir, int depth, i32 fd);
    static void recursive_find(const char* dir, const char* pattern, i32 fd);
};

} // namespace acos::shell
