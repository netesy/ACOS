#include <acos/types.h>
#include <kernel/hal/console.h>

extern "C" {

int printf(const char* format, ...) {
    // Very basic printf that just prints the string
    acos::hal::console_print(format);
    return 0;
}

}
