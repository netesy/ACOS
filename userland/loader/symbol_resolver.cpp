#include "symbol_resolver.h"
#include "library_manager.h"
#include "elf_dynamic.h"

namespace acos::loader {

namespace {

bool same_symbol(const char* lhs, const char* rhs) {
    if (!lhs || !rhs) {
        return false;
    }
    usize i = 0;
    while (lhs[i] && rhs[i] && lhs[i] == rhs[i]) {
        ++i;
    }
    return lhs[i] == rhs[i];
}

} // namespace

void* SymbolResolver::resolve(const char* name, void* handle) {
    if (!name) return nullptr;

    for (usize i = 0; i < LibraryManager::count(); i++) {
        LoadedLibrary* lib = LibraryManager::at(i);
        if (!lib) {
            continue;
        }
        if (handle && static_cast<void*>(lib) != handle) {
            continue;
        }
        if (!lib->dynsym || !lib->dynstr) {
            continue;
        }

        const Elf64_Sym* symbols = static_cast<const Elf64_Sym*>(lib->dynsym);
        for (usize sym_idx = 0; sym_idx < lib->dynsym_count; sym_idx++) {
            const char* sym_name = lib->dynstr + symbols[sym_idx].st_name;
            if (same_symbol(sym_name, name) && symbols[sym_idx].st_value != 0) {
                return reinterpret_cast<void*>(lib->base_address + symbols[sym_idx].st_value);
            }
        }
    }

    return nullptr;
}

} // namespace acos::loader
