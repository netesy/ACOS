#include <acos/process.h>
#include <acos/runtime.h>
#include "include/dlfcn.h"
#include <libs/runtime/include/acos/runtime.h>

namespace {
    // Thread-local error message buffer
    thread_local char g_dlerror_buffer[256] = {0};
}

extern "C" {

char* dlerror(void) {
    // Return the last error message, or nullptr if no error
    if (g_dlerror_buffer[0] == '\0') {
        return nullptr;
    }
    
    char* result = g_dlerror_buffer;
    g_dlerror_buffer[0] = '\0'; // Clear for next call
    return result;
}

// Internal function to set error message
void __dlerror_set(const char* msg) {
    if (!msg) {
        g_dlerror_buffer[0] = '\0';
        return;
    }
    
    acos::usize i = 0;
    while (msg[i] && i < 255) {
        g_dlerror_buffer[i] = msg[i];
        i++;
    }
    g_dlerror_buffer[i] = '\0';
}

}
