#include "terminal_session.h"
#include <acos/vfs.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::apps {

TerminalSession::TerminalSession(TerminalBuffer* buffer)
    : m_parser(buffer),
      m_master_write(-1), m_master_read(-1),
      m_shell_process(0), m_reader_thread(0), m_running(false),
      m_on_output(nullptr), m_on_output_arg(nullptr) {}

TerminalSession::~TerminalSession() {
    m_running = false;
    if (m_master_write >= 0) vfs::close(m_master_write);
    if (m_master_read >= 0) vfs::close(m_master_read);
}

bool TerminalSession::start(void (*on_output_callback)(void*), void* callback_arg) {
    m_on_output = on_output_callback;
    m_on_output_arg = callback_arg;

    i32 to_shell[2];
    i32 from_shell[2];

    if (vfs::pipe(to_shell) < 0) return false;
    if (vfs::pipe(from_shell) < 0) {
        vfs::close(to_shell[0]);
        vfs::close(to_shell[1]);
        return false;
    }

    // Temporarily backup FD 0 and FD 1 using dup2
    i32 old_stdin = vfs::open("/dev/console", 0);
    i32 old_stdout = vfs::open("/dev/console", 0);
    vfs::dup2(0, old_stdin);
    vfs::dup2(1, old_stdout);

    // Redirect standard files to pipe ends
    vfs::dup2(to_shell[0], 0);
    vfs::dup2(from_shell[1], 1);
    vfs::dup2(from_shell[1], 2);

    // Create process `/bin/cli.elf`
    u64 proc = syscall(sys::SyscallNum::ProcessCreate, reinterpret_cast<u64>("/bin/cli.elf"), 0, 0, 0, 0);

    // Instantly restore terminal parent's standard I/O
    vfs::dup2(old_stdin, 0);
    vfs::dup2(old_stdout, 1);
    vfs::dup2(old_stdout, 2);

    vfs::close(old_stdin);
    vfs::close(old_stdout);

    // Close unused slave ends
    vfs::close(to_shell[0]);
    vfs::close(from_shell[1]);

    if (proc == 0 || proc == static_cast<u64>(-1)) {
        vfs::close(to_shell[1]);
        vfs::close(from_shell[0]);
        return false;
    }

    m_shell_process = proc;
    m_master_write = to_shell[1];
    m_master_read = from_shell[0];
    m_running = true;

    // Start /bin/cli.elf process
    syscall(sys::SyscallNum::ProcessStart, m_shell_process, 0, 0, 0, 0);

    // Create reader thread
    m_reader_thread = process::create_thread(reader_thread_entry, this);
    if (m_reader_thread != 0) {
        process::start_thread(m_reader_thread);
    }

    return true;
}

void TerminalSession::write_input(const char* data, usize len) {
    if (m_master_write >= 0 && len > 0) {
        vfs::write(m_master_write, data, len);
    }
}

void TerminalSession::reader_thread_entry(void* arg) {
    auto* session = static_cast<TerminalSession*>(arg);
    session->reader_loop();
}

void TerminalSession::reader_loop() {
    char buf[128];
    while (m_running) {
        i32 n = vfs::read(m_master_read, buf, sizeof(buf));
        if (n <= 0) {
            syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0);
            continue;
        }

        m_parser.write(buf, n);

        // Notify view of output update
        if (m_on_output) {
            m_on_output(m_on_output_arg);
        }
    }
}

} // namespace acos::apps
