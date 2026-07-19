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
