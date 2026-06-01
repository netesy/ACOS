#pragma once
#include <acos/types.h>

namespace acos::loader {

struct LoadedLibrary {
    char name[128];
    u64 base_address;
    u64 size;
    u32 ref_count;
    void* dynamic_section;
    void* dynsym;
    const char* dynstr;
    usize dynsym_count;
};

class LibraryManager {
public:
    static LoadedLibrary* load(const char* path);
    static void unload(LoadedLibrary* lib);
    static LoadedLibrary* find_by_name(const char* name);
    static usize count();
    static LoadedLibrary* at(usize index);

private:
    static constexpr usize MAX_LIBRARIES = 64;
    static LoadedLibrary g_libraries[MAX_LIBRARIES];
    static usize g_count;
};

} // namespace acos::loader
