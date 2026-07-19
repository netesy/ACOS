#include <kernel/vfs/console_node.h>
#include <kernel/hal/console.h>
#include <kernel/hal/serial.h>
#include <kernel/scheduler/scheduler.h>

// Microkernel: the console node only writes to the HAL console and serial.
// Graphics-based terminal is now a user-space service.

namespace acos::vfs {

static char g_console_buffer[1024];
static usize g_console_head = 0;
static usize g_console_tail = 0;
static usize g_console_count = 0;

extern "C" void console_push_char(char c) {
    if (g_console_count < 1024) {
        g_console_buffer[g_console_tail] = c;
        g_console_tail = (g_console_tail + 1) % 1024;
        g_console_count++;

        // Debug Logging
        hal::serial_print("[Console] queued '");
        char s[2] = {c, '\0'};
        hal::serial_print(s);
        hal::serial_print("'\n");

        auto* blocked = scheduler::get_console_blocked();
        if (blocked) {
            hal::serial_print("[Console] waking blocked reader\n");
            scheduler::clear_console_blocked(blocked);
            scheduler::wake_thread(blocked);
        }
    }
}

extern "C" char console_pop_char() {
    if (g_console_count == 0) return 0;
    char c = g_console_buffer[g_console_head];
    g_console_head = (g_console_head + 1) % 1024;
    g_console_count--;
    return c;
}

i32 ConsoleNode::read(u64 offset [[maybe_unused]], usize size, void* buffer) {
    if (!buffer || size == 0) return 0;

    char* buf = static_cast<char*>(buffer);
    usize read_bytes = 0;

    while (read_bytes < size) {
        __asm__ volatile("cli");
        char c = console_pop_char();
        if (c != 0) {
            __asm__ volatile("sti");
            buf[read_bytes++] = c;
        } else {
            if (read_bytes > 0) {
                __asm__ volatile("sti");
                break;
            }

            auto* current = scheduler::current_thread();
            scheduler::set_console_blocked(current);
            current->state = scheduler::ThreadState::Blocked;
            __asm__ volatile("sti");
            scheduler::schedule();
        }
    }

    return static_cast<i32>(read_bytes);
}

i32 ConsoleNode::write(u64 offset [[maybe_unused]], usize size, const void* buffer) {
    if (!buffer || size == 0) return 0;

    const char* buf = static_cast<const char*>(buffer);
    // console_print expects a null-terminated string, so we need to be careful.
    // However, console_print is what we have.

    // Create a stack buffer for null-termination if small enough, else print char by char (inefficient)
    if (size < 1024) {
        char temp[1024];
        for (usize i = 0; i < size; i++) temp[i] = buf[i];
        temp[size] = '\0';
        hal::console_print(temp);
    } else {
        // Fallback for large writes - very inefficient but works
        char temp[2] = {0, 0};
        for (usize i = 0; i < size; i++) {
            temp[0] = buf[i];
            hal::console_print(temp);
        }
    }

    // Also mirror to serial for debugging
    for (usize i = 0; i < size; i++) {
        hal::serial_write(buf[i]);
    }

    return static_cast<i32>(size);
}

} // namespace acos::vfs
