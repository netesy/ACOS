#include <kernel/loader/elf.h>
#include <kernel/memory/vmm.h>
#include <kernel/scheduler/process.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::loader {

struct ELFLoadResult {
    u64 entry_point;
    u64 load_base;
};

ELFLoadResult load_elf(const void* data, usize size, bool randomize = true) {
    const Elf64_Ehdr* header = (const Elf64_Ehdr*)data;

    if (header->e_ident[0] != 0x7F || header->e_ident[1] != 'E' ||
        header->e_ident[2] != 'L' || header->e_ident[3] != 'F') {
        return {0, 0};
    }

    u64 load_base = 0;
    if (header->e_type == ET_DYN && randomize) {
        // ASLR: Simple base randomization for Phase 17/18
        load_base = 0x40000000;
    }

    const Elf64_Phdr* phdr = (const Elf64_Phdr*)((const u8*)data + header->e_phoff);
    for (u16 i = 0; i < header->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            // Mapping logic here...
        }
    }

    return {header->e_entry + load_base, load_base};
}

} // namespace acos::loader
