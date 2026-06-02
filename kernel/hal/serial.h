#pragma once
#include <acos/types.h>

namespace acos::hal {

void serial_init();
void serial_write(char c);
void serial_print(const char* s);
bool serial_received();
char serial_read();
bool is_transmit_empty();

} // namespace acos::hal
