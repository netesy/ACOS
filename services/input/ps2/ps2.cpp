#include "ps2.h"
#include <acos/syscall.h>
#include <acos/runtime.h>

#ifdef _KERNEL
#include <kernel/arch/x86_64/smp/lapic.h>
#include <kernel/input/keyboard_manager.h>
#include <kernel/input/mouse_manager.h>
#include <kernel/hal/serial.h>

extern "C" void console_push_char(char c);
#endif

namespace acos::drivers::input {

static constexpr u16 PS2_DATA    = 0x60;
static constexpr u16 PS2_STATUS  = 0x64;
static constexpr u16 PS2_COMMAND = 0x64;

#ifdef _KERNEL
static bool g_shift_pressed = false;
static bool g_ctrl_pressed = false;

static acos::u8 g_mouse_cycle = 0;
static acos::u8 g_mouse_packet[3];

static const char kbd_us_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static const char kbd_us_shift_map[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
#endif

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

    // 5. Initialize PS/2 Mouse Data Reporting
    write_command(0xD4); // Tell controller to route next byte to auxiliary device
    write_data(0xF6);    // Set defaults command
    read_data();         // Read ACK

    write_command(0xD4); // Tell controller to route next byte to auxiliary device
    write_data(0xF4);    // Enable data reporting command
    read_data();         // Read ACK
}

void PS2Controller::handle_interrupt() {
    u8 scancode;
    __asm__ volatile("inb %1, %0" : "=a"(scancode) : "Nd"(PS2_DATA));
}

void PS2Controller::handle_keyboard_interrupt() {
#ifdef _KERNEL
    acos::u8 scancode = inb(PS2_DATA);

    // Let the InputManager / KeyboardManager consume the keyboard event
    acos::input::KeyboardManager::handle_scancode(scancode);

    acos::hal::serial_print("[PS2] IRQ1 received\n");
    acos::hal::serial_print("[PS2] scancode=");
    acos::hal::serial_print_hex(scancode);
    acos::hal::serial_print("\n");

    if (scancode == 0x2A || scancode == 0x36) {
        g_shift_pressed = true;
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        g_shift_pressed = false;
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }

    if (scancode == 0x1D) {
        g_ctrl_pressed = true;
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x9D) {
        g_ctrl_pressed = false;
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }

    if (scancode == 0x48) { // Up Arrow
        console_push_char('\033'); console_push_char('['); console_push_char('A');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x50) { // Down Arrow
        console_push_char('\033'); console_push_char('['); console_push_char('B');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x4B) { // Left Arrow
        console_push_char('\033'); console_push_char('['); console_push_char('D');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x4D) { // Right Arrow
        console_push_char('\033'); console_push_char('['); console_push_char('C');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x47) { // Home Key
        console_push_char('\033'); console_push_char('['); console_push_char('H');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x4F) { // End Key
        console_push_char('\033'); console_push_char('['); console_push_char('F');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }
    if (scancode == 0x53) { // Delete Key
        console_push_char('\033'); console_push_char('['); console_push_char('3'); console_push_char('~');
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }

    if (scancode & 0x80) {
        // Release event
        acos::arch::x86_64::LocalApic::eoi();
        return;
    }

    if (scancode < 128) {
        if (g_ctrl_pressed) {
            if (scancode == 0x2E) { // Ctrl+C
                console_push_char(0x03);
                acos::arch::x86_64::LocalApic::eoi();
                return;
            }
            if (scancode == 0x20) { // Ctrl+D
                console_push_char(0x04);
                acos::arch::x86_64::LocalApic::eoi();
                return;
            }
            if (scancode == 0x26) { // Ctrl+L
                console_push_char(0x0C);
                acos::arch::x86_64::LocalApic::eoi();
                return;
            }
        }

        char ascii = g_shift_pressed ? kbd_us_shift_map[scancode] : kbd_us_map[scancode];
        if (ascii != 0) {
            acos::hal::serial_print("[PS2] ascii='");
            char s[2] = {ascii, '\0'};
            acos::hal::serial_print(s);
            acos::hal::serial_print("'\n");
            console_push_char(ascii);
        }
    }

    acos::arch::x86_64::LocalApic::eoi();
#endif
}

void PS2Controller::handle_mouse_interrupt() {
#ifdef _KERNEL
    acos::u8 data = inb(PS2_DATA);
    if (g_mouse_cycle == 0) {
        if ((data & 8) == 0) {
            acos::arch::x86_64::LocalApic::eoi();
            return; // Out of sync, ignore
        }
        g_mouse_packet[0] = data;
        g_mouse_cycle = 1;
    } else if (g_mouse_cycle == 1) {
        g_mouse_packet[1] = data;
        g_mouse_cycle = 2;
    } else if (g_mouse_cycle == 2) {
        g_mouse_packet[2] = data;
        g_mouse_cycle = 0;

        bool left = (g_mouse_packet[0] & 1) != 0;
        bool right = (g_mouse_packet[0] & 2) != 0;
        bool middle = (g_mouse_packet[0] & 4) != 0;

        acos::i32 dx = g_mouse_packet[1];
        acos::i32 dy = g_mouse_packet[2];

        if (g_mouse_packet[0] & 0x10) dx |= ~0xFF;
        if (g_mouse_packet[0] & 0x20) dy |= ~0xFF;

        // Relative coordinates are positive upwards for PS/2 mouse, but positive downwards on screen.
        dy = -dy;

        acos::input::MouseManager::handle_movement(dx, dy);
        acos::input::MouseManager::handle_button(0, left);
        acos::input::MouseManager::handle_button(1, right);
        acos::input::MouseManager::handle_button(2, middle);
    }
    acos::arch::x86_64::LocalApic::eoi();
#endif
}

} // namespace acos::drivers::input
