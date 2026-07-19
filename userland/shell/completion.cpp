#include "completion.h"
#include <acos/vfs.h>
#include <acos/syscall.h>
#include <acos/syscall_nums.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

static const char* builtins_list[] = {
    "help", "version", "clear", "pwd", "cd", "ls", "cat", "echo",
    "mkdir", "rmdir", "touch", "rm", "cp", "mv", "stat", "tree",
    "find", "which", "env", "set", "alias", "unalias", "history",
    "time", "sleep", "mount", "ps", "kill", "reboot", "shutdown",
    "exit"
};
static constexpr usize builtins_count = sizeof(builtins_list) / sizeof(builtins_list[0]);

int CompletionManager::complete(const char* current_cwd, const char* partial, char* out_completed, bool& out_is_dir) {
    out_completed[0] = '\0';
    out_is_dir = false;

    if (!partial) return 0;

    char dir_path[1024];
    char prefix[256];

    // Split partial into directory path and file prefix
    int last_slash = -1;
    for (int i = 0; partial[i]; i++) {
        if (partial[i] == '/') last_slash = i;
    }

    if (last_slash != -1) {
        // Contains slashes
        if (partial[0] == '/') {
            // Absolute path
            memcpy(dir_path, partial, last_slash + 1);
            dir_path[last_slash + 1] = '\0';
        } else {
            // Relative path
            usize cwd_len = strlen(current_cwd);
            memcpy(dir_path, current_cwd, cwd_len);
            if (cwd_len > 0 && current_cwd[cwd_len-1] != '/') {
                dir_path[cwd_len] = '/';
                cwd_len++;
            }
            memcpy(dir_path + cwd_len, partial, last_slash + 1);
            dir_path[cwd_len + last_slash + 1] = '\0';
        }

        usize p_idx = 0;
        for (int i = last_slash + 1; partial[i]; i++) {
            if (p_idx < 255) prefix[p_idx++] = partial[i];
        }
        prefix[p_idx] = '\0';
    } else {
        // Current directory
        usize cwd_len = strlen(current_cwd);
        memcpy(dir_path, current_cwd, cwd_len);
        if (cwd_len > 0 && current_cwd[cwd_len-1] != '/') {
            dir_path[cwd_len] = '/';
            cwd_len++;
        }
        dir_path[cwd_len] = '\0';

        usize p_idx = 0;
        while (partial[p_idx] && p_idx < 255) {
            prefix[p_idx] = partial[p_idx];
            p_idx++;
        }
        prefix[p_idx] = '\0';
    }

    // Candidate storage
    static char candidates[64][256];
    static bool candidate_is_dir[64];
    int candidate_count = 0;

    // If it does not contain a slash, we can also match builtins!
    if (last_slash == -1) {
        usize plen = strlen(prefix);
        for (usize i = 0; i < builtins_count; i++) {
            bool prefix_match = true;
            for (usize j = 0; j < plen; j++) {
                if (prefix[j] != builtins_list[i][j]) {
                    prefix_match = false;
                    break;
                }
            }
            if (prefix_match && candidate_count < 64) {
                usize clen = strlen(builtins_list[i]);
                memcpy(candidates[candidate_count], builtins_list[i], clen + 1);
                candidate_is_dir[candidate_count] = false;
                candidate_count++;
            }
        }
    }

    // Now query the VFS directory
    static acos::vfs::DirectoryEntry entries[32];
    i32 n_entries = acos::vfs::read_dir(dir_path, entries, 32);
    if (n_entries >= 0) {
        usize plen = strlen(prefix);
        for (i32 i = 0; i < n_entries; i++) {
            bool prefix_match = true;
            for (usize j = 0; j < plen; j++) {
                if (prefix[j] != entries[i].name[j]) {
                    prefix_match = false;
                    break;
                }
            }
            // Exclude "." and ".." unless explicitly requested
            if (prefix_match && entries[i].name[0] == '.' && plen == 0) {
                prefix_match = false;
            }
            if (prefix_match && candidate_count < 64) {
                usize clen = strlen(entries[i].name);
                memcpy(candidates[candidate_count], entries[i].name, clen + 1);
                candidate_is_dir[candidate_count] = (entries[i].type == acos::vfs::NodeType::Directory);
                candidate_count++;
            }
        }
    }

    if (candidate_count == 0) {
        return 0;
    }

    if (candidate_count == 1) {
        // Unique match found! Fill the missing suffix
        usize plen = strlen(prefix);
        usize clen = strlen(candidates[0]);
        if (clen >= plen) {
            usize out_len = 0;
            for (usize i = plen; i < clen; i++) {
                out_completed[out_len++] = candidates[0][i];
            }
            out_completed[out_len] = '\0';
            out_is_dir = candidate_is_dir[0];
            return 1;
        }
        return 0;
    }

    // Multiple candidates. Print options on a new line!
    // We will output a newline and print all matches, then wait for prompt redraw
    // By returning candidate_count, the caller can decide to print options.
    return candidate_count;
}

} // namespace acos::shell
