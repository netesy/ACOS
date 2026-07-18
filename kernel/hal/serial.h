#pragma once
#include <acos/types.h>

namespace acos::hal {

void serial_init();
void serial_write(char c);
void serial_print(const char* s);
void serial_print_hex(u64 val);
bool serial_received();
char serial_read();
bool is_transmit_empty();

} // namespace acos::hal
