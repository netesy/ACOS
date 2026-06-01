#pragma once
#include <acos/types.h>

namespace acos::loader {

using Elf64_Addr = u64;
using Elf64_Off = u64;
using Elf64_Half = u16;
using Elf64_Word = u32;
using Elf64_Xword = u64;

struct Elf64_Ehdr {
    unsigned char e_ident[16];
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;
    Elf64_Off e_phoff;
    Elf64_Off e_shoff;
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
};

struct Elf64_Phdr {
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
};

// ELF Constants
static constexpr u8 ELFMAG0 = 0x7f;
static constexpr u8 ELFMAG1 = 'E';
static constexpr u8 ELFMAG2 = 'L';
static constexpr u8 ELFMAG3 = 'F';

static constexpr u8 ELFCLASS64 = 2;
static constexpr u8 ELFDATA2LSB = 1;
static constexpr Elf64_Half EM_X86_64 = 62;

// ELF file types
static constexpr Elf64_Half ET_EXEC = 2;
static constexpr Elf64_Half ET_DYN = 3;

static constexpr Elf64_Word PT_LOAD = 1;

static constexpr Elf64_Word PF_X = 0x1;
static constexpr Elf64_Word PF_W = 0x2;
static constexpr Elf64_Word PF_R = 0x4;

bool validate_elf(const Elf64_Ehdr* header);

} // namespace acos::loader
