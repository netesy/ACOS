#pragma once
#include <acos/types.h>
#include "terminal_buffer.h"
#include "terminal_parser.h"

namespace acos::apps {

class TerminalSession {
public:
    TerminalSession(TerminalBuffer* buffer);
    ~TerminalSession();

    bool start(void (*on_output_callback)(void*), void* callback_arg);

    void write_input(const char* data, usize len);

    bool is_running() const { return m_running; }

private:
    static void reader_thread_entry(void* arg);
    void reader_loop();

    TerminalParser m_parser;

    i32 m_master_write; // PTY Master write end (to shell stdin)
    i32 m_master_read;  // PTY Master read end (from shell stdout)

    u64 m_shell_process;
    u64 m_reader_thread;
    bool m_running;

    void (*m_on_output) (void*);
    void* m_on_output_arg;
};

} // namespace acos::apps
