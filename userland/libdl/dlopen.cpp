#include "include/dlfcn.h"
#include <userland/loader/rtld.h>

extern "C" {

void* dlopen(const char* filename, int flags) {
    if (!filename) return nullptr;
    
    // Load library using runtime loader
    LoadedLibrary* lib = acos::loader::LibraryManager::load(filename);
    if (!lib) return nullptr;
    
    // Return opaque handle (cast library pointer to void*)
    return (void*)lib;
}

}
