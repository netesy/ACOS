#include "include/dlfcn.h"
#include <userland/loader/library_manager.h>

extern "C" {

void* dlopen(const char* filename, int flags) {
    (void)flags;
    if (!filename) return nullptr;
    
    // Load library using runtime loader
    acos::loader::LoadedLibrary* lib = acos::loader::LibraryManager::load(filename);
    if (!lib) return nullptr;
    
    // Return opaque handle (cast library pointer to void*)
    return (void*)lib;
}

}
