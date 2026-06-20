#include <kernel/loader/process_loader.h>
#include <kernel/loader/elf_loader.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/paging.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/memory/heap.h>

extern "C" [[noreturn]] void enter_user_mode(acos::u64 entry, acos::u64 stack);

namespace acos::loader {

static void* kernel_thread_stub(void* arg) {
    (void)arg;
    auto* thr = scheduler::current_thread();
    __asm__ volatile("mov %0, %%cr3" : : "r"(thr->parent->address_space->pml4_phys()));
    enter_user_mode(thr->stack_top, 0x700000000000);
}

scheduler::Process* create_process_from_elf(const char* name, const void* elf_data, usize size) {
    (void)name;
    scheduler::Process* p = scheduler::Process::create();
    if (!p) return nullptr;
    u64 entry_point = 0;
    if (elf_data && size > 0) {
        ELFLoadResult load_result = ElfLoader::load_executable(p->address_space, elf_data, size);
        if (!load_result.success) return nullptr;
        entry_point = load_result.entry_point;
    }
    u64 stack_phys = memory::pmm_alloc();
    u64 stack_virt = 0x700000000000;
    p->address_space->map(stack_virt - 4096, stack_phys, memory::PageFlags::User | memory::PageFlags::Writable | memory::PageFlags::Present);
    scheduler::Thread* t = scheduler::create_thread(kernel_thread_stub, nullptr);
    if (!t) return nullptr;
    t->parent = p;
    t->is_user = true;
    t->stack_top = entry_point;
    p->primary_thread = t;
    return p;
}
}
