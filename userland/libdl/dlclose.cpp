#include "include/dlfcn.h"
#include <userland/loader/library_manager.h>

extern "C" {

int dlclose(void* handle) {
    if (!handle) {
        return -1;
    }
    acos::loader::LibraryManager::unload(static_cast<acos::loader::LoadedLibrary*>(handle));
    return 0;
}

}
