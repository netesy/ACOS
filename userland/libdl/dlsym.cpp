#include "include/dlfcn.h"
#include <userland/loader/symbol_resolver.h>

extern "C" {

void* dlsym(void* handle, const char* symbol) {
    return acos::loader::SymbolResolver::resolve(symbol, handle);
}

}
