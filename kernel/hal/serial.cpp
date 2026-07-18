#include <acos/types.h>

namespace acos::hal {

static constexpr uint16_t COM1 = 0x3F8;

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void serial_init() {
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);    // Set divisor to 3 (38400 baud)
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

bool serial_received() {
    return inb(COM1 + 5) & 1;
}

char serial_read() {
    while (!serial_received());
    return inb(COM1);
}

bool is_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

void serial_write(char a) {
    while (!is_transmit_empty());
    outb(COM1, a);
}

void serial_print(const char* s) {
    while (*s) {
        serial_write(*s++);
    }
}

void serial_print_hex(u64 val) {
    char buf[19];
    buf[0] = '0';
    buf[1] = 'x';
    for (int i = 0; i < 16; i++) {
        int shift = 60 - (i * 4);
        u8 hex = (val >> shift) & 0xF;
        buf[2 + i] = (hex < 10) ? ('0' + hex) : ('A' + (hex - 10));
    }
    buf[18] = '\0';
    serial_print(buf);
}

} // namespace acos::hal
