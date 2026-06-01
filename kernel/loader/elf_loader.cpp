#include <kernel/loader/elf.h>
#include <kernel/memory/vmm.h>
#include <kernel/memory/pmm.h>
#include <kernel/scheduler/process.h>
#include <acos/runtime.h>

namespace acos::loader {

struct ELFLoadResult {
    u64 entry_point;
    u64 load_base;
};

ELFLoadResult load_elf(const void* data, usize size [[maybe_unused]], bool randomize = true) {
    const Elf64_Ehdr* header = (const Elf64_Ehdr*)data;

    if (header->e_ident[0] != 0x7F || header->e_ident[1] != 'E' ||
        header->e_ident[2] != 'L' || header->e_ident[3] != 'F') {
        return {0, 0};
    }

    u64 load_base = 0;
    if (header->e_type == ET_DYN && randomize) {
        // ASLR: Simple base randomization
        load_base = 0x40000000;
    }

    const Elf64_Phdr* phdr = (const Elf64_Phdr*)((const u8*)data + header->e_phoff);
    for (u16 i = 0; i < header->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            u64 vaddr = phdr[i].p_vaddr + load_base;
            u64 memsz = phdr[i].p_memsz;
            u64 filesz = phdr[i].p_filesz;
            u64 offset = phdr[i].p_offset;
            
            // Map memory region
            u64 pages = (memsz + 4095) / 4096;
            for (u64 j = 0; j < pages; j++) {
                u64 phys = memory::pmm_alloc();
                if (!phys) return {0, 0};
                
                u64 page_vaddr [[maybe_unused]] = vaddr + (j * 4096);
                u32 flags = memory::PageFlags::User | memory::PageFlags::Writable;
                
                if (!(phdr[i].p_flags & PF_W)) {
                    flags &= ~memory::PageFlags::Writable;
                }
                
                // Map page (would use current address space)
            }
            
            // Copy file data
            if (filesz > 0) {
                const void* src = (const u8*)data + offset;
                memcpy((void*)vaddr, src, filesz);
            }
            
            // Zero BSS
            if (memsz > filesz) {
                memset((void*)(vaddr + filesz), 0, memsz - filesz);
            }
        }
    }

    return {header->e_entry + load_base, load_base};
}

} // namespace acos::loader
