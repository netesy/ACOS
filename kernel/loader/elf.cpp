#include <kernel/loader/elf.h>

namespace acos::loader {

bool validate_elf(const Elf64_Ehdr* header) {
    if (!header) return false;

    // Magic
    if (header->e_ident[0] != ELFMAG0 || header->e_ident[1] != ELFMAG1 ||
        header->e_ident[2] != ELFMAG2 || header->e_ident[3] != ELFMAG3) {
        return false;
    }

    // Class & Data
    if (header->e_ident[4] != ELFCLASS64 || header->e_ident[5] != ELFDATA2LSB) {
        return false;
    }

    // Machine
    if (header->e_machine != EM_X86_64) {
        return false;
    }

    return true;
}

} // namespace acos::loader
