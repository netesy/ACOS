#include <boot/efi.h>
#include <acos/boot_info.h>

struct Elf64_Ehdr {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

struct Elf64_Phdr {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
};

#define PT_LOAD 1

extern "C" void* memset(void* dest, int value, acos::usize count) {
    auto* out = static_cast<acos::u8*>(dest);
    for (acos::usize i = 0; i < count; ++i) {
        out[i] = static_cast<acos::u8>(value);
    }
    return dest;
}

extern "C" void* memcpy(void* dest, const void* src, acos::usize count) {
    auto* out = static_cast<acos::u8*>(dest);
    const auto* in = static_cast<const acos::u8*>(src);
    for (acos::usize i = 0; i < count; ++i) {
        out[i] = in[i];
    }
    return dest;
}

namespace {

constexpr efi::Status EFI_SUCCESS = 0;
constexpr efi::Status EFI_LOAD_ERROR = 0x8000000000000001ULL;
constexpr efi::Status EFI_INVALID_PARAMETER = 0x8000000000000002ULL;
constexpr efi::Status EFI_NOT_FOUND = 0x800000000000000EULL;
constexpr acos::u64 KERNEL_MIN_ADDRESS = 0x100000;
constexpr acos::u64 KERNEL_MAX_ADDRESS = 0x40000000;
constexpr int EFI_ALL_HANDLES = 0;
constexpr int EFI_BY_PROTOCOL = 2;



void connect_all_controllers(efi::SystemTable* systemTable) {
    if (!systemTable || !systemTable->bootServices) {
        return;
    }

    acos::usize handleCount = 0;
    efi::Handle* handles = nullptr;
    efi::Status status = systemTable->bootServices->locateHandleBuffer(EFI_ALL_HANDLES,
                                                                       nullptr,
                                                                       nullptr,
                                                                       &handleCount,
                                                                       &handles);
    if (status != EFI_SUCCESS || !handles) {
        return;
    }

    for (acos::usize i = 0; i < handleCount; ++i) {
        systemTable->bootServices->connectController(handles[i], nullptr, nullptr, 1);
    }

    systemTable->bootServices->freePool(handles);
}

efi::GraphicsOutputProtocol* locate_graphics_output(efi::SystemTable* systemTable) {
    if (!systemTable || !systemTable->bootServices) {
        return nullptr;
    }

    efi::GraphicsOutputProtocol* gop = nullptr;
    efi::Status status = systemTable->bootServices->locateProtocol(&efi::GraphicsOutputProtocolGuid, nullptr, (void**)&gop);
    if (status == EFI_SUCCESS && gop && gop->mode && gop->mode->info) {
        return gop;
    }

    connect_all_controllers(systemTable);
    status = systemTable->bootServices->locateProtocol(&efi::GraphicsOutputProtocolGuid, nullptr, (void**)&gop);
    if (status == EFI_SUCCESS && gop && gop->mode && gop->mode->info) {
        return gop;
    }

    acos::usize handleCount = 0;
    efi::Handle* handles = nullptr;
    status = systemTable->bootServices->locateHandleBuffer(EFI_BY_PROTOCOL,
                                                           &efi::GraphicsOutputProtocolGuid,
                                                           nullptr,
                                                           &handleCount,
                                                           &handles);
    if (status != EFI_SUCCESS || !handles) {
        return nullptr;
    }

    for (acos::usize i = 0; i < handleCount; ++i) {
        gop = nullptr;
        status = systemTable->bootServices->handleProtocol(handles[i], &efi::GraphicsOutputProtocolGuid, (void**)&gop);
        if (status == EFI_SUCCESS && gop && gop->mode && gop->mode->info) {
            systemTable->bootServices->freePool(handles);
            return gop;
        }
    }

    systemTable->bootServices->freePool(handles);
    return nullptr;
}

void print(efi::SystemTable* systemTable, const char16_t* message) {
    if (systemTable && systemTable->conOut && systemTable->conOut->outputString) {
        systemTable->conOut->outputString(systemTable->conOut, message);
    }
}

void print_hex(efi::SystemTable* systemTable, acos::u64 value) {
    char16_t buffer[19] = u"0x0000000000000000";
    for (int i = 0; i < 16; ++i) {
        const acos::u8 nibble = static_cast<acos::u8>((value >> ((15 - i) * 4)) & 0xF);
        buffer[2 + i] = static_cast<char16_t>(nibble < 10 ? u'0' + nibble : u'A' + (nibble - 10));
    }
    print(systemTable, buffer);
}

[[noreturn]] efi::Status fail(efi::SystemTable* systemTable, const char16_t* message, efi::Status status) {
    print(systemTable, u"ACOS Bootloader: ERROR: ");
    print(systemTable, message);
    print(systemTable, u" status=");
    print_hex(systemTable, status);
    print(systemTable, u"\r\n");

    while (true) {
        __asm__("hlt");
    }
}

bool valid_elf_header(const Elf64_Ehdr& header) {
    return header.e_ident[0] == 0x7F &&
           header.e_ident[1] == 'E' &&
           header.e_ident[2] == 'L' &&
           header.e_ident[3] == 'F' &&
           header.e_ident[4] == 2 &&
           header.e_machine == 0x3E &&
           header.e_ehsize == sizeof(Elf64_Ehdr) &&
           header.e_phentsize == sizeof(Elf64_Phdr) &&
           header.e_phnum > 0;
}


[[noreturn]] void enter_kernel(acos::u64 entryAddress, acos::BootInfo* bootInfo) {
#if defined(__x86_64__)
    __asm__ volatile(
        "movq %1, %%rdi\n"
        "jmp *%0\n"
        :
        : "r"(entryAddress), "r"(bootInfo)
        : "rdi", "memory");
#endif
    while (true) {
        __asm__("hlt");
    }
}

bool valid_load_segment(const Elf64_Phdr& phdr) {
    if (phdr.p_type != PT_LOAD) {
        return true;
    }
    if (phdr.p_memsz < phdr.p_filesz || phdr.p_memsz == 0) {
        return false;
    }
    if (phdr.p_paddr < KERNEL_MIN_ADDRESS) {
        return false;
    }
    if (phdr.p_paddr > KERNEL_MAX_ADDRESS || phdr.p_memsz > KERNEL_MAX_ADDRESS - phdr.p_paddr) {
        return false;
    }
    return true;
}

} // namespace

extern "C" efi::Status efi_main(efi::Handle imageHandle, efi::SystemTable* systemTable) {
    print(systemTable, u"ACOS Bootloader: Loading Kernel...\r\n");

    efi::GraphicsOutputProtocol* gop = locate_graphics_output(systemTable);
    efi::Status status = EFI_SUCCESS;
    const bool hasFramebuffer = gop && gop->mode && gop->mode->info;
    if (!hasFramebuffer) {
        print(systemTable, u"ACOS Bootloader: GOP unavailable; continuing without framebuffer.\r\n");
    }

    efi::LoadedImageProtocol* loadedImage = nullptr;
    status = systemTable->bootServices->handleProtocol(imageHandle, &efi::LoadedImageProtocolGuid, (void**)&loadedImage);
    if (status != EFI_SUCCESS || !loadedImage) {
        return fail(systemTable, u"LoadedImage protocol unavailable", status);
    }

    efi::SimpleFileSystemProtocol* fs = nullptr;
    status = systemTable->bootServices->handleProtocol(loadedImage->deviceHandle, &efi::SimpleFileSystemProtocolGuid, (void**)&fs);
    if (status != EFI_SUCCESS || !fs) {
        return fail(systemTable, u"SimpleFileSystem protocol unavailable", status);
    }

    efi::FileProtocol* root = nullptr;
    status = fs->openVolume(fs, &root);
    if (status != EFI_SUCCESS || !root) {
        return fail(systemTable, u"cannot open boot volume", status);
    }

    efi::FileProtocol* kernelFile = nullptr;
    status = root->open(root, &kernelFile, u"\\kernel.elf", 1 /* READ */, 0);
    if (status != EFI_SUCCESS || !kernelFile) {
        status = root->open(root, &kernelFile, u"kernel.elf", 1 /* READ */, 0);
    }
    if (status != EFI_SUCCESS || !kernelFile) {
        status = root->open(root, &kernelFile, u"KERNEL.ELF", 1 /* READ */, 0);
    }
    if (status != EFI_SUCCESS || !kernelFile) {
        return fail(systemTable, u"cannot open kernel.elf", status == EFI_SUCCESS ? EFI_NOT_FOUND : status);
    }

    Elf64_Ehdr header = {};
    acos::usize headerSize = sizeof(header);
    status = kernelFile->read(kernelFile, &headerSize, &header);
    if (status != EFI_SUCCESS || headerSize != sizeof(header) || !valid_elf_header(header)) {
        return fail(systemTable, u"invalid kernel ELF header", status == EFI_SUCCESS ? EFI_LOAD_ERROR : status);
    }

    if (header.e_entry < KERNEL_MIN_ADDRESS || header.e_entry >= KERNEL_MAX_ADDRESS) {
        return fail(systemTable, u"kernel entry outside allowed physical range", EFI_INVALID_PARAMETER);
    }

    print(systemTable, u"ACOS Bootloader: Kernel entry ");
    print_hex(systemTable, header.e_entry);
    print(systemTable, u"\r\n");

    for (acos::u16 i = 0; i < header.e_phnum; ++i) {
        status = kernelFile->setPosition(kernelFile, header.e_phoff + (static_cast<acos::u64>(i) * header.e_phentsize));
        if (status != EFI_SUCCESS) {
            return fail(systemTable, u"cannot seek program header", status);
        }

        Elf64_Phdr phdr = {};
        acos::usize phdrSize = sizeof(phdr);
        status = kernelFile->read(kernelFile, &phdrSize, &phdr);
        if (status != EFI_SUCCESS || phdrSize != sizeof(phdr)) {
            return fail(systemTable, u"cannot read program header", status == EFI_SUCCESS ? EFI_LOAD_ERROR : status);
        }

        if (!valid_load_segment(phdr)) {
            return fail(systemTable, u"invalid kernel load segment", EFI_INVALID_PARAMETER);
        }

        if (phdr.p_type == PT_LOAD) {
            const acos::usize pages = static_cast<acos::usize>((phdr.p_memsz + 4095) / 4096);
            acos::u64 segmentBase = phdr.p_paddr;
            status = systemTable->bootServices->allocatePages(efi::AllocateType::AllocateAddress, efi::MemoryType::LoaderData, pages, &segmentBase);
            if (status != EFI_SUCCESS || segmentBase != phdr.p_paddr) {
                return fail(systemTable, u"cannot allocate kernel segment", status == EFI_SUCCESS ? EFI_LOAD_ERROR : status);
            }

            status = kernelFile->setPosition(kernelFile, phdr.p_offset);
            if (status != EFI_SUCCESS) {
                return fail(systemTable, u"cannot seek kernel segment", status);
            }

            acos::usize size = static_cast<acos::usize>(phdr.p_filesz);
            status = kernelFile->read(kernelFile, &size, (void*)segmentBase);
            if (status != EFI_SUCCESS || size != phdr.p_filesz) {
                return fail(systemTable, u"cannot read kernel segment", status == EFI_SUCCESS ? EFI_LOAD_ERROR : status);
            }

            systemTable->bootServices->setMem((void*)(segmentBase + phdr.p_filesz), static_cast<acos::usize>(phdr.p_memsz - phdr.p_filesz), 0);
        }
    }

    static acos::BootInfo bootInfo;
    static acos::FramebufferInfo fbInfo;
    bootInfo.memoryMap = nullptr;
    bootInfo.cpuInfo = nullptr;
    bootInfo.framebuffer = nullptr;
    bootInfo.acpi = nullptr;
    bootInfo.initrd = nullptr;
    bootInfo.bootTime = 0;
    fbInfo.base = 0;
    fbInfo.size = 0;
    fbInfo.width = 0;
    fbInfo.height = 0;
    fbInfo.pitch = 0;
    fbInfo.bpp = 0;
    if (hasFramebuffer) {
        fbInfo.base = gop->mode->frameBufferBase;
        fbInfo.size = gop->mode->frameBufferSize;
        fbInfo.width = gop->mode->info->horizontalResolution;
        fbInfo.height = gop->mode->info->verticalResolution;
        fbInfo.pitch = gop->mode->info->pixelsPerScanLine;
        fbInfo.bpp = 32;
        bootInfo.framebuffer = &fbInfo;
    }

    acos::usize mapSize = 0;
    efi::MemoryDescriptor* map = nullptr;
    acos::usize mapKey = 0;
    acos::usize descSize = 0;
    acos::u32 descVer = 0;
    status = systemTable->bootServices->getMemoryMap(&mapSize, nullptr, &mapKey, &descSize, &descVer);
    if (descSize == 0) {
        return fail(systemTable, u"invalid memory map descriptor size", status);
    }

    mapSize += 2 * descSize;
    status = systemTable->bootServices->allocatePool(efi::MemoryType::LoaderData, mapSize, (void**)&map);
    if (status != EFI_SUCCESS || !map) {
        return fail(systemTable, u"cannot allocate memory map", status);
    }

    status = systemTable->bootServices->getMemoryMap(&mapSize, map, &mapKey, &descSize, &descVer);
    if (status != EFI_SUCCESS) {
        return fail(systemTable, u"cannot read memory map", status);
    }

    status = systemTable->bootServices->exitBootServices(imageHandle, mapKey);
    if (status != EFI_SUCCESS) {
        status = systemTable->bootServices->getMemoryMap(&mapSize, map, &mapKey, &descSize, &descVer);
        if (status == EFI_SUCCESS) {
            status = systemTable->bootServices->exitBootServices(imageHandle, mapKey);
        }
        if (status != EFI_SUCCESS) {
            return fail(systemTable, u"ExitBootServices failed", status);
        }
    }

    enter_kernel(header.e_entry, &bootInfo);
}
