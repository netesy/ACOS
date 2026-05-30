#include <kernel/loader/process_loader.h>
#include <kernel/loader/elf_loader.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/paging.h>

namespace acos::loader {

scheduler::Process* create_process_from_elf(const char* name, const void* elf_data, usize size) {
    (void)name;

    // 1. Create Process
    scheduler::Process* p = scheduler::Process::create();
    if (!p) return nullptr;

    // 2. Load ELF into AddressSpace
    if (!ElfLoader::load(p->address_space, elf_data, size)) {
        // cleanup would happen here
        return nullptr;
    }

    // 3. Setup User Stack
    u64 stack_phys = memory::pmm_alloc();
    u64 stack_virt = 0x700000000000;
    p->address_space->map(stack_virt - 4096, stack_phys, memory::PageFlags::User | memory::PageFlags::Writable);

    // 4. Create Initial Thread
    // TCB setup with entry point from ELF would happen here

    return p;
}

} // namespace acos::loader
