#pragma once
#include <kernel/loader/elf.h>
#include <kernel/memory/address_space.h>

namespace acos::loader {

struct ELFLoadResult {
    bool success;
    u64 entry_point;
    u64 load_base;
};

class ElfLoader {
public:
    static ELFLoadResult load_executable(memory::AddressSpace* target_as, const void* elf_data, usize size);
    static bool load(memory::AddressSpace* target_as, const void* elf_data, usize size);
};

} // namespace acos::loader
