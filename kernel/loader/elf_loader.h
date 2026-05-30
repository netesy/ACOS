#pragma once
#include <kernel/loader/elf.h>
#include <kernel/memory/address_space.h>

namespace acos::loader {

class ElfLoader {
public:
    static bool load(memory::AddressSpace* target_as, const void* elf_data, usize size);
};

} // namespace acos::loader
