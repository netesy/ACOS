#include "ps2.h"
#include <acos/syscall.h>
#include <acos/runtime.h>

namespace acos::drivers::input {

static constexpr u16 PS2_DATA    = 0x60;
static constexpr u16 PS2_STATUS  = 0x64;
static constexpr u16 PS2_COMMAND = 0x64;

void PS2Controller::wait_write() {
    u8 status;
    do {
        __asm__ volatile("inb %1, %0" : "=a"(status) : "Nd"(PS2_STATUS));
    } while (status & 2);
}

void PS2Controller::wait_read() {
    u8 status;
    do {
        __asm__ volatile("inb %1, %0" : "=a"(status) : "Nd"(PS2_STATUS));
    } while (!(status & 1));
}

void PS2Controller::write_command(u8 cmd) {
    wait_write();
    __asm__ volatile("outb %0, %1" : : "a"(cmd), "Nd"(PS2_COMMAND));
}

u8 PS2Controller::read_data() {
    wait_read();
    u8 data;
    __asm__ volatile("inb %1, %0" : "=a"(data) : "Nd"(PS2_DATA));
    return data;
}

void PS2Controller::write_data(u8 data) {
    wait_write();
    __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(PS2_DATA));
}

void PS2Controller::init() {
    // 1. Disable devices
    write_command(0xAD); // Disable KBD
    write_command(0xA7); // Disable Mouse

    // 2. Flush buffer
    u8 status;
    __asm__ volatile("inb %1, %0" : "=a"(status) : "Nd"(PS2_STATUS));
    if (status & 1) read_data();

    // 3. Set config byte
    write_command(0x20); // Read config
    u8 config = read_data();
    config |= 3; // Enable interrupts for both
    write_command(0x60); // Write config
    write_data(config);

    // 4. Enable devices
    write_command(0xAE);
    write_command(0xA8);
}

void PS2Controller::handle_interrupt() {
    u8 scancode;
    __asm__ volatile("inb %1, %0" : "=a"(scancode) : "Nd"(PS2_DATA));

    // In user-space, we'd send an IPC to the input_router or desktop_shell
}

} // namespace acos::drivers::input
