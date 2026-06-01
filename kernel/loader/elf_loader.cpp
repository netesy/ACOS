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
        const u64 pages = (phdr[i].p_memsz + 4095) / 4096;
        u32 flags = memory::PageFlags::User;
        if ((phdr[i].p_flags & PF_W) != 0) {
            flags |= memory::PageFlags::Writable;
        }

        for (u64 page = 0; page < pages; ++page) {
            const u64 phys = memory::pmm_alloc();
            if (!phys) {
                return {false, 0, 0};
            }
            if (!target_as->map(vaddr + page * 4096, phys, flags)) {
                return {false, 0, 0};
            }
        }

        if (phdr[i].p_filesz > 0) {
            memcpy(reinterpret_cast<void*>(vaddr), reinterpret_cast<const u8*>(elf_data) + phdr[i].p_offset, phdr[i].p_filesz);
        }
        if (phdr[i].p_memsz > phdr[i].p_filesz) {
            memset(reinterpret_cast<void*>(vaddr + phdr[i].p_filesz), 0, phdr[i].p_memsz - phdr[i].p_filesz);
        }
    }

    return {true, header->e_entry + load_base, load_base};
}

bool ElfLoader::load(memory::AddressSpace* target_as, const void* elf_data, usize size) {
    return load_executable(target_as, elf_data, size).success;
}

} // namespace acos::loader
