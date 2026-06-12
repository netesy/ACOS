#include <acos/process.h>
#include <acos/runtime.h>
#include "library_manager.h"
#include <libs/runtime/include/acos/runtime.h>
#include "relocation.h"

namespace acos::loader {

LoadedLibrary LibraryManager::g_libraries[MAX_LIBRARIES];
usize LibraryManager::g_count = 0;

LoadedLibrary* LibraryManager::load(const char* path) {
    LoadedLibrary* existing = find_by_name(path);
    if (existing) {
        existing->ref_count++;
        return existing;
    }

    if (g_count >= MAX_LIBRARIES) return nullptr;

    LoadedLibrary* lib = &g_libraries[g_count++];
    usize i = 0;
    while(path[i] && i < 127) { lib->name[i] = path[i]; i++; }
    lib->name[i] = '\0';

    lib->ref_count = 1;
    lib->size = 0;
    lib->dynamic_section = nullptr;
    lib->dynsym = nullptr;
    lib->dynstr = nullptr;
    lib->dynsym_count = 0;

    // In a stable implementation, we calculate a random base address if PIE
    lib->base_address = 0x50000000 + (g_count * 0x1000000);

    // Load file and map to base_address...

    RelocationEngine::apply(lib);

    return lib;
}

void LibraryManager::unload(LoadedLibrary* lib) {
    if (lib && lib->ref_count > 0) {
        lib->ref_count--;
    }
}

LoadedLibrary* LibraryManager::find_by_name(const char* name) {
    for (usize i = 0; i < g_count; i++) {
        bool match = true;
        for (usize j = 0; name[j] || g_libraries[i].name[j]; j++) {
            if (name[j] != g_libraries[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) return &g_libraries[i];
    }
    return nullptr;
}

usize LibraryManager::count() {
    return g_count;
}

LoadedLibrary* LibraryManager::at(usize index) {
    if (index >= g_count) {
        return nullptr;
    }
    return &g_libraries[index];
}

} // namespace acos::loader
