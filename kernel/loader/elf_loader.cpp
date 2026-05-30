#include <kernel/loader/elf_loader.h>
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>

namespace acos::loader {

bool ElfLoader::load(memory::AddressSpace* target_as, const void* elf_data, usize size) {
    (void)size;
    const Elf64_Ehdr* header = reinterpret_cast<const Elf64_Ehdr*>(elf_data);
    if (!validate_elf(header)) return false;

    const u8* data = reinterpret_cast<const u8*>(elf_data);
    const Elf64_Phdr* phdr = reinterpret_cast<const Elf64_Phdr*>(data + header->e_phoff);

    for (int i = 0; i < header->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            u64 flags = memory::PageFlags::User;
            if (phdr[i].p_flags & PF_W) flags |= memory::PageFlags::Writable;
            if (!(phdr[i].p_flags & PF_X)) flags |= memory::PageFlags::NoExecute;

            u64 virt_start = phdr[i].p_vaddr;
            u64 virt_end = virt_start + phdr[i].p_memsz;
            u64 phys_offset = phdr[i].p_offset;

            for (u64 v = virt_start & ~0xFFFULL; v < virt_end; v += 4096) {
                u64 phys = memory::pmm_alloc();
                target_as->map(v, phys, flags);

                u64 v_offset = (v < virt_start) ? (virt_start - v) : 0;
                u64 p_offset = (v > virt_start) ? (v - virt_start) : 0;

                u64 copy_size = (4096 - v_offset);
                if (p_offset + copy_size > phdr[i].p_filesz) {
                    if (p_offset < phdr[i].p_filesz) {
                        copy_size = phdr[i].p_filesz - p_offset;
                    } else {
                        copy_size = 0;
                    }
                }

                if (copy_size > 0) {
                    memcpy(reinterpret_cast<void*>(phys + v_offset),
                           data + phys_offset + p_offset,
                           copy_size);
                }

                if (copy_size < (4096 - v_offset)) {
                    memset(reinterpret_cast<void*>(phys + v_offset + copy_size),
                           0,
                           (4096 - v_offset) - copy_size);
                }
            }
        }
    }

    return true;
}

} // namespace acos::loader
