#include <acos/process.h>
#include <acos/runtime.h>
#include "relocation.h"
#include "elf_dynamic.h"
#include "symbol_resolver.h"

namespace acos::loader {

bool RelocationEngine::apply(LoadedLibrary* lib) {
    if (!lib || !lib->dynamic_section) return false;
    
    const u64 base = lib->base_address;
    Elf64_Dyn* dyn = static_cast<Elf64_Dyn*>(lib->dynamic_section);
    
    Elf64_Rela* rela_table = nullptr;
    usize rela_size = 0;
    usize rela_ent = sizeof(Elf64_Rela);

    for (usize i = 0; dyn[i].d_tag != DT_NULL; i++) {
        if (dyn[i].d_tag == DT_RELA) {
            // Address of Rela table might be absolute or relative depending on linker
            u64 ptr = dyn[i].d_un.d_ptr;
            if (ptr < base) {
                rela_table = reinterpret_cast<Elf64_Rela*>(base + ptr);
            } else {
                rela_table = reinterpret_cast<Elf64_Rela*>(ptr);
            }
        } else if (dyn[i].d_tag == DT_RELASZ) {
            rela_size = dyn[i].d_un.d_val;
        } else if (dyn[i].d_tag == DT_RELAENT) {
            rela_ent = dyn[i].d_un.d_val;
        }
    }

    if (rela_table && rela_size > 0 && rela_ent > 0) {
        usize count = rela_size / rela_ent;
        for (usize i = 0; i < count; i++) {
            Elf64_Rela* rela = reinterpret_cast<Elf64_Rela*>(reinterpret_cast<u8*>(rela_table) + i * rela_ent);
            u32 type = ELF64_R_TYPE(rela->r_info);
            u32 sym_idx = ELF64_R_SYM(rela->r_info);
            u64* target = reinterpret_cast<u64*>(base + rela->r_offset);

            if (type == R_X86_64_RELATIVE) {
                *target = base + rela->r_addend;
            } else if (type == R_X86_64_GLOB_DAT || type == R_X86_64_JUMP_SLOT || type == R_X86_64_64) {
                if (lib->dynsym && lib->dynstr) {
                    Elf64_Sym* symbols = static_cast<Elf64_Sym*>(lib->dynsym);
                    const char* name = lib->dynstr + symbols[sym_idx].st_name;
                    void* resolved = SymbolResolver::resolve(name);
                    if (resolved) {
                        *target = reinterpret_cast<u64>(resolved) + rela->r_addend;
                    }
                }
            }
        }
    }
    
    return true;
}

} // namespace acos::loader
