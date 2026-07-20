#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>

namespace acos::drivers::input {

class PS2Controller {
public:
    static void init();
    static void handle_interrupt();

    static void handle_keyboard_interrupt();
    static void handle_mouse_interrupt();

private:
    static void wait_write();
    static void wait_read();
    static void write_command(u8 cmd);
    static u8 read_data();
    static void write_data(u8 data);
};

} // namespace acos::drivers::input
