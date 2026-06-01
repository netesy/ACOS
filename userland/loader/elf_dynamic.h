#pragma once
#include <acos/types.h>

namespace acos::loader {

struct Elf64_Dyn {
    i64 d_tag;
    union {
        u64 d_val;
        u64 d_ptr;
    } d_un;
};

#define DT_NULL     0
#define DT_NEEDED   1
#define DT_PLTGOT   3
#define DT_STRTAB   5
#define DT_SYMTAB   6
#define DT_RELA     7
#define DT_RELASZ   8
#define DT_RELAENT  9
#define DT_STRSZ    10
#define DT_SYMENT   11
#define DT_INIT     12
#define DT_FINI     13
#define DT_SONAME   14
#define DT_RPATH    15
#define DT_SYMBOLIC 16
#define DT_REL      17
#define DT_RELSZ    18
#define DT_RELENT   19
#define DT_PLTREL   20
#define DT_DEBUG    21
#define DT_TEXTREL  22
#define DT_JMPREL   23
#define DT_BIND_NOW 24

struct Elf64_Sym {
    u32 st_name;
    u8 st_info;
    u8 st_other;
    u16 st_shndx;
    u64 st_value;
    u64 st_size;
};

struct Elf64_Rela {
    u64 r_offset;
    u64 r_info;
    i64 r_addend;
};

#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i) & 0xffffffffL)

#define R_X86_64_64        1
#define R_X86_64_RELATIVE  8
#define R_X86_64_GLOB_DAT  6
#define R_X86_64_JUMP_SLOT 7

} // namespace acos::loader
