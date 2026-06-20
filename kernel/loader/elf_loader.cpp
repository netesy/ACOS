#include <kernel/loader/elf_loader.h>
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>

namespace acos::loader {

namespace {

bool valid_header(const Elf64_Ehdr* header, usize size) {
    if (!header || size < sizeof(Elf64_Ehdr)) {
        return false;
    }
    if (header->e_ident[0] != ELFMAG0 || header->e_ident[1] != ELFMAG1 ||
        header->e_ident[2] != ELFMAG2 || header->e_ident[3] != ELFMAG3) {
        return false;
    }
    if (header->e_ident[4] != ELFCLASS64 || header->e_ident[5] != ELFDATA2LSB) {
        return false;
    }
    if (header->e_machine != EM_X86_64 || (header->e_type != ET_EXEC && header->e_type != ET_DYN)) {
        return false;
    }
    if (header->e_phentsize != sizeof(Elf64_Phdr)) {
        return false;
    }
    return header->e_phoff + (static_cast<usize>(header->e_phnum) * sizeof(Elf64_Phdr)) <= size;
}

} // namespace

ELFLoadResult ElfLoader::load_executable(memory::AddressSpace* target_as, const void* elf_data, usize size) {
    if (!target_as || !elf_data) {
        return {false, 0, 0};
    }

    const Elf64_Ehdr* header = reinterpret_cast<const Elf64_Ehdr*>(elf_data);
    if (!valid_header(header, size)) {
        return {false, 0, 0};
    }

    const u64 load_base = (header->e_type == ET_DYN) ? 0x40000000 : 0;
    const Elf64_Phdr* phdr = reinterpret_cast<const Elf64_Phdr*>(reinterpret_cast<const u8*>(elf_data) + header->e_phoff);

    for (u16 i = 0; i < header->e_phnum; ++i) {
        if (phdr[i].p_type != PT_LOAD) {
            continue;
        }
        if (phdr[i].p_offset + phdr[i].p_filesz > size || phdr[i].p_memsz < phdr[i].p_filesz) {
            return {false, 0, 0};
        }

        const u64 vaddr = phdr[i].p_vaddr + load_base;
        const u64 memsz = phdr[i].p_memsz;
        const u64 filesz = phdr[i].p_filesz;
        const u64 offset = phdr[i].p_offset;

        u64 start_page = vaddr & ~0xFFFULL;
        u64 end_page = (vaddr + memsz + 4095) & ~0xFFFULL;

        u32 flags = memory::PageFlags::User | memory::PageFlags::Present;
        if ((phdr[i].p_flags & PF_W) != 0) {
            flags |= memory::PageFlags::Writable;
        }

        for (u64 page_addr = start_page; page_addr < end_page; page_addr += 4096) {
            u64 phys = target_as->translate(page_addr);

            // If the page is already identity mapped (phys == virt), we MUST re-map it
            // to a new physical page to avoid corrupting kernel/MMIO memory.
            if (!phys || phys == page_addr) {
                phys = memory::pmm_alloc();
                if (!phys) return {false, 0, 0};
                if (!target_as->map(page_addr, phys, flags)) return {false, 0, 0};
                memset(reinterpret_cast<void*>(phys), 0, 4096);
            }

            u64 copy_start = (vaddr > page_addr) ? vaddr : page_addr;
            u64 copy_end = ((vaddr + filesz) < (page_addr + 4096)) ? (vaddr + filesz) : (page_addr + 4096);

            if (copy_start < copy_end) {
                u64 off_in_page = copy_start - page_addr;
                u64 off_in_elf = copy_start - vaddr;
                u64 size_to_copy = copy_end - copy_start;
                memcpy(reinterpret_cast<void*>(phys + off_in_page),
                       reinterpret_cast<const u8*>(elf_data) + offset + off_in_elf,
                       size_to_copy);
            }

            u64 bss_start = (vaddr + filesz > page_addr) ? vaddr + filesz : page_addr;
            u64 bss_end = (vaddr + memsz < page_addr + 4096) ? vaddr + memsz : page_addr + 4096;

            if (bss_start < bss_end) {
                u64 off_in_page = bss_start - page_addr;
                u64 size_to_zero = bss_end - bss_start;
                memset(reinterpret_cast<void*>(phys + off_in_page), 0, size_to_zero);
            }
        }
    }

    return {true, header->e_entry + load_base, load_base};
}

bool ElfLoader::load(memory::AddressSpace* target_as, const void* elf_data, usize size) {
    return load_executable(target_as, elf_data, size).success;
}

} // namespace acos::loader
