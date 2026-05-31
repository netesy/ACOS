#include "symbol_resolver.h"
#include "library_manager.h"

namespace acos::loader {

void* SymbolResolver::resolve(const char* name, void* handle) {
    (void)handle;
    // In a full implementation, this iterates through g_libraries' .dynsym
    // For now, we provide the architecture to be expanded.
    return nullptr;
}

} // namespace acos::loader
