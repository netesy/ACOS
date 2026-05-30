#include <boot/efi.h>
#include <acos/boot_info.h>

extern "C" efi::Status efi_main(efi::Handle imageHandle, efi::SystemTable* systemTable) {
    systemTable->conOut->outputString(systemTable->conOut, u"ACOS Bootloader v1.1 starting...\r\n");

    // 1. Get Graphics Output Protocol
    efi::GraphicsOutputProtocol* gop = nullptr;
    efi::Status status = systemTable->bootServices->locateProtocol(&efi::GraphicsOutputProtocolGuid, nullptr, (void**)&gop);

    if (status != 0 || !gop) {
        systemTable->conOut->outputString(systemTable->conOut, u"Failed to get GOP\r\n");
        return status;
    }

    // 2. Prepare BootInfo
    static acos::BootInfo bootInfo = {};
    static acos::FramebufferInfo fbInfo = {};

    fbInfo.base = gop->mode->frameBufferBase;
    fbInfo.size = gop->mode->frameBufferSize;
    fbInfo.width = gop->mode->info->horizontalResolution;
    fbInfo.height = gop->mode->info->verticalResolution;
    fbInfo.pitch = gop->mode->info->pixelsPerScanLine;
    fbInfo.bpp = 32;

    bootInfo.framebuffer = &fbInfo;

    // 3. Load Kernel ELF (Simplified)
    // In a full implementation, we'd use SimpleFileSystemProtocol to find and read kernel.elf
    // and then parse its ELF headers to load segments into memory.

    // 4. Get Memory Map
    acos::usize memoryMapSize = 0;
    efi::MemoryDescriptor* memoryMap = nullptr;
    acos::usize mapKey = 0;
    acos::usize descriptorSize = 0;
    acos::u32 descriptorVersion = 0;

    systemTable->bootServices->getMemoryMap(&memoryMapSize, nullptr, &mapKey, &descriptorSize, &descriptorVersion);
    memoryMapSize += 2 * descriptorSize;
    systemTable->bootServices->allocatePool(efi::MemoryType::LoaderData, memoryMapSize, (void**)&memoryMap);
    systemTable->bootServices->getMemoryMap(&memoryMapSize, memoryMap, &mapKey, &descriptorSize, &descriptorVersion);

    static acos::MemoryMap acosMap = {};
    // Placeholder: pass memory map directly in Phase 2
    bootInfo.memoryMap = &acosMap;

    systemTable->conOut->outputString(systemTable->conOut, u"Exiting Boot Services. See you in the Kernel.\r\n");

    // 5. Exit Boot Services
    status = systemTable->bootServices->exitBootServices(imageHandle, mapKey);
    if (status != 0) {
        systemTable->conOut->outputString(systemTable->conOut, u"Failed to exit boot services\r\n");
        return status;
    }

    // 6. Jump to Kernel Entry
    // We assume the kernel is loaded at a fixed physical address or we jump to its entry point.
    // For this prototype, we'll use a fixed entry point address (e.g., 0x100000) or handle it via loader.

    typedef void (*KernelEntry)(acos::BootInfo*);
    KernelEntry kernelMain = (KernelEntry)0x100000; // Placeholder address from linker script
    kernelMain(&bootInfo);

    while(1) { __asm__("hlt"); }
    return 0;
}
