#include "include/dlfcn.h"
#include <userland/loader/rtld.h>

extern "C" {

void* dlsym(void* handle, const char* symbol) {
    (void)handle;
    return acos::loader::RuntimeLoader::get_symbol(symbol);
}

}
