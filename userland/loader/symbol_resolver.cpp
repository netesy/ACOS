#include "symbol_resolver.h"
#include "library_manager.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::loader {

void* SymbolResolver::resolve(const char* name, void* handle) {
    if (!name) return nullptr;
    
    // Symbol resolution process:
    // 1. Get library from handle (or search all if handle is nullptr)
    // 2. Access dynamic symbol table (.dynsym)
    // 3. Access dynamic string table (.dynstr)
    // 4. Iterate through symbols looking for name match
    // 5. Return symbol value (address)
    
    for (usize i = 0; i < LibraryManager::g_count; i++) {
        LoadedLibrary* lib = &LibraryManager::g_libraries[i];
        
        // If handle specified, only search that library
        if (handle && (void*)lib != handle) continue;
        
        // Search dynamic symbol table
        if (!lib->dynsym || !lib->dynstr) continue;
        
        // Iterate through dynamic symbols
        for (usize sym_idx = 0; sym_idx < lib->dynsym_count; sym_idx++) {
            // Get symbol name from dynamic string table
            const char* sym_name = lib->dynstr + lib->dynsym[sym_idx].st_name;
            
            // Compare symbol names
            if (acos::runtime::strcmp(sym_name, name) == 0) {
                // Return symbol value (address)
                u64 sym_value = lib->dynsym[sym_idx].st_value;
                
                // If symbol is in this library, add base address
                if (sym_value != 0) {
                    return (void*)(lib->base_address + sym_value);
                }
            }
        }
    }
    
    // Symbol not found
    return nullptr;
}

} // namespace acos::loader
