#include <acos/boot_info.h>

namespace acos::hal {
    void serial_init();
    void serial_print(const char* s);
    void console_init(FramebufferInfo* fb);
    void console_clear(u32 color);
    void console_print(const char* s, u32 color = 0xFFFFFFFF);
    void gdt_init();
    void idt_init();
}

namespace acos::memory {
    void pmm_init(BootInfo* bootInfo);
}

namespace acos::scheduler {
    void scheduler_init();
    struct Process {
        static Process* create();
    };
}

namespace acos::security {
    enum class DomainType { System };
    struct Domain {
        static Domain* create(DomainType type);
    };
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel Phase 3: Process System Starting...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel Phase 3 - Process System\n");
    }

    acos::hal::gdt_init();
    acos::hal::idt_init();
    acos::memory::pmm_init(bootInfo);
    acos::scheduler::scheduler_init();

    // Initialize Phase 3 Components
    acos::security::Domain::create(acos::security::DomainType::System);
    acos::scheduler::Process::create();

    acos::hal::console_print("Process and Domain Managers Initialized.\n");
    acos::hal::serial_print("ACOS Kernel Phase 3 Success. Isolation Active.\n");

    while (true) {
        __asm__("hlt");
    }
}
