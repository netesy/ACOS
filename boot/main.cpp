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

extern "C" efi::Status efi_main(efi::Handle imageHandle, efi::SystemTable* systemTable) {
    systemTable->conOut->outputString(systemTable->conOut, u"ACOS Bootloader: Loading Kernel...\r\n");

    // 1. Get GOP
    efi::GraphicsOutputProtocol* gop = nullptr;
    systemTable->bootServices->locateProtocol(&efi::GraphicsOutputProtocolGuid, nullptr, (void**)&gop);

    // 2. Open File System
    efi::LoadedImageProtocol* loadedImage = nullptr;
    systemTable->bootServices->handleProtocol(imageHandle, &efi::LoadedImageProtocolGuid, (void**)&loadedImage);

    efi::SimpleFileSystemProtocol* fs = nullptr;
    systemTable->bootServices->handleProtocol(loadedImage->deviceHandle, &efi::SimpleFileSystemProtocolGuid, (void**)&fs);

    efi::FileProtocol* root = nullptr;
    fs->openVolume(fs, &root);

    efi::FileProtocol* kernelFile = nullptr;
    root->open(root, &kernelFile, u"kernel.elf", 1 /* READ */, 0);

    // 3. Read ELF Header
    Elf64_Ehdr header;
    acos::usize headerSize = sizeof(header);
    kernelFile->read(kernelFile, &headerSize, &header);

    // 4. Load Segments
    for (int i = 0; i < header.e_phnum; i++) {
        kernelFile->setPosition(kernelFile, header.e_phoff + (i * header.e_phentsize));
        Elf64_Phdr phdr;
        acos::usize phdrSize = sizeof(phdr);
        kernelFile->read(kernelFile, &phdrSize, &phdr);

        if (phdr.p_type == PT_LOAD) {
            acos::usize pages = (phdr.p_memsz + 4095) / 4096;
            acos::u64 segmentBase = phdr.p_paddr;
            systemTable->bootServices->allocatePages(efi::AllocateType::AllocateAddress, efi::MemoryType::LoaderData, pages, &segmentBase);

            kernelFile->setPosition(kernelFile, phdr.p_offset);
            acos::usize size = phdr.p_filesz;
            kernelFile->read(kernelFile, &size, (void*)segmentBase);

            // Zero out remaining memory in segment
            systemTable->bootServices->setMem((void*)(segmentBase + phdr.p_filesz), phdr.p_memsz - phdr.p_filesz, 0);
        }
    }

    // 5. Memory Map
    static acos::BootInfo bootInfo = {};
    static acos::FramebufferInfo fbInfo = {};
    fbInfo.base = gop->mode->frameBufferBase;
    fbInfo.size = gop->mode->frameBufferSize;
    fbInfo.width = gop->mode->info->horizontalResolution;
    fbInfo.height = gop->mode->info->verticalResolution;
    fbInfo.pitch = gop->mode->info->pixelsPerScanLine;
    bootInfo.framebuffer = &fbInfo;

    acos::usize mapSize = 0;
    efi::MemoryDescriptor* map = nullptr;
    acos::usize mapKey, descSize;
    acos::u32 descVer;
    systemTable->bootServices->getMemoryMap(&mapSize, nullptr, &mapKey, &descSize, &descVer);
    mapSize += 2 * descSize;
    systemTable->bootServices->allocatePool(efi::MemoryType::LoaderData, mapSize, (void**)&map);
    systemTable->bootServices->getMemoryMap(&mapSize, map, &mapKey, &descSize, &descVer);

    // 6. Exit & Jump
    systemTable->bootServices->exitBootServices(imageHandle, mapKey);

    typedef void (*KernelEntry)(acos::BootInfo*);
    KernelEntry entry = (KernelEntry)header.e_entry;
    entry(&bootInfo);

    while(1) { __asm__("hlt"); }
    return 0;
}
