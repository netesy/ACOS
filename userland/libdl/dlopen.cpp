#include "include/dlfcn.h"
#include <userland/loader/rtld.h>

extern "C" {

void* dlopen(const char* filename, int flags) {
    (void)flags;
    if (acos::loader::RuntimeLoader::load_library(filename)) {
        return (void*)1; // Dummy handle
    }
    return nullptr;
}

}
