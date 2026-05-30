#include <kernel/process/loader.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/paging.h>

namespace acos::process {

scheduler::Process* create_user_process(const char* name, u64 entry_point) {
    (void)name;
    scheduler::Process* p = scheduler::Process::create();
    if (!p) return nullptr;

    u64 stack_phys = memory::pmm_alloc();
    u64 stack_virt = 0x700000000000;
    p->address_space->map(stack_virt - 4096, stack_phys, memory::PageFlags::User | memory::PageFlags::Writable);

    (void)entry_point;

    return p;
}

} // namespace acos::process
