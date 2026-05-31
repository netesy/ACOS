#include <acos/types.h>

extern "C" {

void exit(int status) {
    (void)status;
    // Call ACOS exit syscall
    while(1) __asm__("hlt");
}

int abs(int j) {
    return j < 0 ? -j : j;
}

}
