#include "cli_shell.h"
#include "console_reader.h"
#include "parser.h"
#include "executor.h"
#include "variables.h"
#include "history.h"
#include <acos/process.h>
#include <acos/vfs.h>
#include <acos/syscall.h>
#include <acos/syscall_nums.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

CLIShell::CLIShell() : m_running(true) {
    ::memcpy(m_cwd, "/", 2);
    m_console_fd = static_cast<i32>(syscall(sys::SyscallNum::FileOpen, reinterpret_cast<u64>("/dev/console"), 0, 0, 0, 0));
}

void CLIShell::execute_startup_scripts() {
    const char* scripts[] = { "/etc/profile", "/users/default/.asadrc" };

    for (usize s = 0; s < 2; s++) {
        const char* script_path = scripts[s];
        i32 fd = vfs::open(script_path, 0);
        if (fd < 0) continue;

        acos::process::log("CLIShell: Executing startup script ");
        acos::process::log(script_path);
        acos::process::log("\n");

        static char line_buf[1024];
        usize len = 0;
        char c;

        while (true) {
            i32 n = vfs::read(fd, &c, 1);
            if (n <= 0) {
                if (len > 0) {
                    line_buf[len] = '\0';
                    perform_command_substitution(line_buf);
                    static Pipeline pipeline;
                    if (CommandLineParser::parse(line_buf, pipeline)) {
                        ShellExecutor::execute(pipeline, m_cwd, m_console_fd);
                        // Cleanup allocated argv
                        for (int i = 0; i < pipeline.command_count; i++) {
                            for (int j = 0; j < pipeline.commands[i].argc; j++) {
                                memory::kfree(pipeline.commands[i].argv[j]);
                            }
                        }
                    }
                }
                break;
            }

            if (c == '\n' || c == '\r') {
                if (len > 0) {
                    line_buf[len] = '\0';
                    perform_command_substitution(line_buf);
                    static Pipeline pipeline;
                    if (CommandLineParser::parse(line_buf, pipeline)) {
                        ShellExecutor::execute(pipeline, m_cwd, m_console_fd);
                        // Cleanup allocated argv
                        for (int i = 0; i < pipeline.command_count; i++) {
                            for (int j = 0; j < pipeline.commands[i].argc; j++) {
                                memory::kfree(pipeline.commands[i].argv[j]);
                            }
                        }
                    }
                    len = 0;
                }
            } else {
                if (len < 1023) {
                    line_buf[len++] = c;
                }
            }
        }
        vfs::close(fd);
    }
}

void CLIShell::perform_command_substitution(char* buffer) {
    char* sub_start = nullptr;
    for (int k = 0; buffer[k]; k++) {
        if (buffer[k] == '$' && buffer[k+1] == '(') {
            sub_start = buffer + k;
            break;
        }
    }

    if (sub_start) {
        char* sub_end = sub_start + 2;
        int paren_count = 1;
        while (*sub_end) {
            if (*sub_end == '(') paren_count++;
            else if (*sub_end == ')') {
                paren_count--;
                if (paren_count == 0) break;
            }
            sub_end++;
        }

        if (*sub_end == ')') {
            char inner_cmd[512];
            usize inner_len = sub_end - (sub_start + 2);
            if (inner_len > 511) inner_len = 511;
            memcpy(inner_cmd, sub_start + 2, inner_len);
            inner_cmd[inner_len] = '\0';

            // Recursively evaluate any command substitution inside the inner command first!
            perform_command_substitution(inner_cmd);

            // Create a pipe for capturing stdout
            i32 sub_pipe_fds[2];
            if (vfs::pipe(sub_pipe_fds) >= 0) {
                static Pipeline sub_pipeline;
                if (CommandLineParser::parse(inner_cmd, sub_pipeline)) {
                    // Temporarily redirect stdout to pipe writer
                    i32 saved_stdout = vfs::open("/dev/console", 0);
                    vfs::dup2(1, saved_stdout);
                    vfs::dup2(sub_pipe_fds[1], 1);
                    vfs::close(sub_pipe_fds[1]);

                    // Execute inner command
                    ShellExecutor::execute(sub_pipeline, m_cwd, m_console_fd);

                    // Restore stdout in parent shell
                    vfs::dup2(saved_stdout, 1);
                    vfs::close(saved_stdout);

                    // Clean pipeline arguments memory
                    for (int sc = 0; sc < sub_pipeline.command_count; sc++) {
                        for (int sa = 0; sa < sub_pipeline.commands[sc].argc; sa++) {
                            memory::kfree(sub_pipeline.commands[sc].argv[sa]);
                        }
                    }

                    // Read captured stdout from read end of pipe
                    char sub_output[1024] = {0};
                    i32 n_bytes = vfs::read(sub_pipe_fds[0], sub_output, 1023);
                    vfs::close(sub_pipe_fds[0]);

                    if (n_bytes > 0) {
                        sub_output[n_bytes] = '\0';
                        while (n_bytes > 0 && (sub_output[n_bytes - 1] == '\n' || sub_output[n_bytes - 1] == '\r' || sub_output[n_bytes - 1] == ' ')) {
                            sub_output[--n_bytes] = '\0';
                        }
                    }

                    static char temp_reconstructed[2048];
                    usize prefix_len = sub_start - buffer;
                    memcpy(temp_reconstructed, buffer, prefix_len);
                    usize output_len = strlen(sub_output);
                    memcpy(temp_reconstructed + prefix_len, sub_output, output_len);
                    usize suffix_len = strlen(sub_end + 1);
                    memcpy(temp_reconstructed + prefix_len + output_len, sub_end + 1, suffix_len + 1);

                    memcpy(buffer, temp_reconstructed, strlen(temp_reconstructed) + 1);
                } else {
                    vfs::close(sub_pipe_fds[0]);
                    vfs::close(sub_pipe_fds[1]);
                }
            }
        }
    }
}

void CLIShell::run() {
    ShellExecutor::init();

    // Create a mock startup script so it runs successfully
    // We can try to touch it or create directories if supported, or just proceed
    execute_startup_scripts();

    static char input_buffer[1024];
    acos::process::log("CLIShell: Interactive production REPL loop starting...\n");

    // Display welcome banner
    syscall(sys::SyscallNum::FileWrite, m_console_fd, reinterpret_cast<u64>("Asade Capabilities CLI Shell v1.0\n"), 34, 0, 0);

    while (m_running) {
        if (!ConsoleReader::read_line(m_console_fd, m_cwd, input_buffer, 1024)) {
            continue;
        }

        if (input_buffer[0] == '\0') {
            continue;
        }

        // Add to history
        HistoryManager::add(input_buffer);

        // Pre-parse Alias Expansion
        // We look up the first word in the input buffer. If it's an alias, we replace it.
        char first_word[128];
        int fw_len = 0;
        while (input_buffer[fw_len] && input_buffer[fw_len] != ' ' && input_buffer[fw_len] != '\t' && fw_len < 127) {
            first_word[fw_len] = input_buffer[fw_len];
            fw_len++;
        }
        first_word[fw_len] = '\0';

        const char* expansion = VariablesManager::get_alias(first_word);
        static char expanded_buffer[2048];
        if (expansion) {
            usize elen = strlen(expansion);
            memcpy(expanded_buffer, expansion, elen);
            usize rem_len = strlen(input_buffer + fw_len);
            memcpy(expanded_buffer + elen, input_buffer + fw_len, rem_len + 1);
        } else {
            memcpy(expanded_buffer, input_buffer, strlen(input_buffer) + 1);
        }

        // Perform command substitution
        perform_command_substitution(expanded_buffer);

        // Process exit check
        if (strcmp(expanded_buffer, "exit") == 0) {
            m_running = false;
            break;
        }

        // Parse expanded line into Pipeline
        static Pipeline pipeline;
        if (CommandLineParser::parse(expanded_buffer, pipeline)) {
            ShellExecutor::execute(pipeline, m_cwd, m_console_fd);

            // Deallocate memories to prevent memory leaks
            for (int i = 0; i < pipeline.command_count; i++) {
                for (int j = 0; j < pipeline.commands[i].argc; j++) {
                    memory::kfree(pipeline.commands[i].argv[j]);
                }
            }
        }
    }

    // Clean exit
    syscall(sys::SyscallNum::Exit, 0, 0, 0, 0, 0);
}

} // namespace acos::shell
