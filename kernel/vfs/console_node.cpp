#include <kernel/vfs/console_node.h>
#include <kernel/hal/console.h>
#include <kernel/hal/serial.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::vfs {

i32 ConsoleNode::read(u64 offset [[maybe_unused]], usize size, void* buffer) {
    if (!buffer || size == 0) return 0;

    char* buf = static_cast<char*>(buffer);
    usize read_bytes = 0;

    while (read_bytes < size) {
        if (hal::serial_received()) {
            buf[read_bytes++] = hal::serial_read();
        } else {
            // If we have read at least one byte, return what we have.
            if (read_bytes > 0) break;

            // Block this thread on console I/O. The idle loop polls
            // serial_received() and calls wake_thread() when data
            // arrives, which re-enqueues us and triggers a context
            // switch back here.
            scheduler::Thread* self = scheduler::current_thread();
            if (self) {
                scheduler::set_console_blocked(self);
                scheduler::block_thread(self);
                scheduler::clear_console_blocked(self);
            }
            // Fallback: halt CPU until next hardware event in case
            // the idle loop hasn't polled yet or we're on the boot
            // thread with no scheduler context.
            __asm__ volatile("hlt");
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
