#include "linux_loader.h"
#include <kernel/loader/elf.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/vfs/vfs.h>

namespace acos::compat::linux {

bool LinuxLoader::load_linux_binary(const char* path) {
    u64 fd = acos::vfs::VFS::open(path, 0);
    if (fd == (u64)-1) return false;

    Elf64_Ehdr header;
    if (acos::vfs::VFS::read(fd, &header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        acos::vfs::VFS::close(fd);
        return false;
    }

    // Validate Linux ELF64
    if (header.e_ident[0] != 0x7F || header.e_ident[1] != 'E' ||
        header.e_ident[2] != 'L' || header.e_ident[3] != 'F' ||
        header.e_ident[4] != 2) { // ELFCLASS64
        acos::vfs::VFS::close(fd);
        return false;
    }

    // Architecture for mapping segments and setting up aux vector
    acos::vfs::VFS::close(fd);
    return true;
}

} // namespace acos::compat::linux
