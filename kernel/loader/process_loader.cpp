#include <kernel/loader/process_loader.h>
#include <kernel/loader/elf_loader.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/paging.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/memory/heap.h>

namespace acos::loader {

scheduler::Process* create_process_from_elf(const char* name, const void* elf_data, usize size) {
    (void)name;

    // 1. Create Process
    scheduler::Process* p = scheduler::Process::create();
    if (!p) return nullptr;

    // 2. Load ELF
    if (elf_data && size > 0) {
        if (!ElfLoader::load(p->address_space, elf_data, size)) return nullptr;
    }

    // 3. Setup User Stack
    u64 stack_phys = memory::pmm_alloc();
    u64 stack_virt = 0x700000000000;
    p->address_space->map(stack_virt - 4096, stack_phys, memory::PageFlags::User | memory::PageFlags::Writable);

    // 4. Create Initial Thread
    scheduler::Thread* t = reinterpret_cast<scheduler::Thread*>(memory::kmalloc(sizeof(scheduler::Thread)));
    t->id = 1; // First thread
    t->parent = p;
    t->state = scheduler::ThreadState::Ready;
    t->is_user = true;

    // Prime the stack for context_switch
    // In a real switch, we'd push a "return to user" stub
    t->stack_pointer = stack_virt - 8;

    scheduler::wake_thread(t);

    return p;
}

} // namespace acos::loader
