#include <kernel/vfs/console_node.h>
#include <kernel/hal/console.h>
#include <kernel/hal/serial.h>

namespace acos::vfs {

i32 ConsoleNode::read(u64 offset [[maybe_unused]], usize size, void* buffer) {
    if (!buffer || size == 0) return 0;

    char* buf = static_cast<char*>(buffer);
    usize read_bytes = 0;

    while (read_bytes < size) {
        if (hal::serial_received()) {
            buf[read_bytes++] = hal::serial_read();
        } else {
            // In a real OS we would block the thread here.
            // For now, if we have read at least one byte, we return.
            if (read_bytes > 0) break;

            // Busy wait for at least one byte
            __asm__("pause");
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
