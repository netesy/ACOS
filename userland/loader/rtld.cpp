#include "rtld.h"
#include "library_manager.h"
#include "symbol_resolver.h"
#include "loader_cache.h"

namespace acos::loader {

void RuntimeLoader::initialize() {
    LoaderCache::init();
}

bool RuntimeLoader::load_library(const char* path) {
    return LibraryManager::load(path) != nullptr;
}

void* RuntimeLoader::get_symbol(const char* name) {
    return SymbolResolver::resolve(name);
}

} // namespace acos::loader
