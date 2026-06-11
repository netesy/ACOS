#include <kernel/vfs/console_node.h>
#include <kernel/hal/console.h>
#include <kernel/hal/serial.h>
#include <services/display/terminal_window.h>
#include <services/display/display_server.h>

// The shell thread is the only thread that runs. The boot thread's
// idle loop never executes because context switching back from the
// shell thread doesn't work yet (no timer interrupt). So the shell
// thread itself drives the display compositor after each hlt and
// after each write.
static void flush_display() {
    if (acos::display::g_terminal_window) {
        acos::display::g_terminal_window->redraw();
    }
    extern acos::display::DisplayServer* g_display_server;
    if (g_display_server) {
        g_display_server->run_tick();
    }
}

namespace acos::vfs {

i32 ConsoleNode::read(u64 offset [[maybe_unused]], usize size, void* buffer) {
    if (!buffer || size == 0) return 0;

    char* buf = static_cast<char*>(buffer);
    usize read_bytes = 0;

    while (read_bytes < size) {
        if (hal::serial_received()) {
            buf[read_bytes++] = hal::serial_read();
        } else {
            // If we already have data, return it now.
            if (read_bytes > 0) break;

            // Halt CPU until next hardware event.
            __asm__ volatile("hlt");

            // Drive the display compositor from the shell thread
            // since the boot thread's idle loop isn't running.
            flush_display();
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

    // Forward to terminal window for display in QEMU graphical output
    if (acos::display::g_terminal_window) {
        acos::display::g_terminal_window->put_string(buf, size);
    }

    return static_cast<i32>(size);
}

} // namespace acos::vfs
