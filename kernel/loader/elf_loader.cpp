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

    // Validate ELF header
    if (header->e_ident[0] != 0x7F || header->e_ident[1] != 'E' ||
        header->e_ident[2] != 'L' || header->e_ident[3] != 'F') {
        return {0, 0};
    }

    u64 load_base = 0;
    if (header->e_type == ET_DYN && randomize) {
        // ASLR: Randomize load base (simplified for now)
        load_base = 0x40000000;
    }

    const Elf64_Phdr* phdr = (const Elf64_Phdr*)((u8*)data + header->e_phoff);
    for (u16 i = 0; i < header->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            // Map segments with offset
            // vmm_map(phdr[i].p_vaddr + load_base, phdr[i].p_memsz, ...)
        }
    }

    return {header->e_entry + load_base, load_base};
}

} // namespace acos::loader
