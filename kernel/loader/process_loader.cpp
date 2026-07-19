#include <kernel/loader/process_loader.h>
#include <kernel/hal/serial.h>
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
    acos::hal::serial_print("[LOADER] kernel_thread_stub entered, thread=");
    acos::hal::serial_print_hex(thr->id);
    acos::hal::serial_print(" entry=");
    acos::hal::serial_print_hex(thr->entry_point);
    acos::hal::serial_print("\n");
    __asm__ volatile("mov %0, %%cr3" : : "r"(thr->parent->address_space->pml4_phys()));
    acos::hal::serial_print("[LOADER] CR3 loaded successfully! Entering Ring 3...\n");
    enter_user_mode(thr->entry_point, 0x700000000000);
}

scheduler::Process* create_process_from_elf(const char* name, const void* elf_data, usize size) {
    (void)name;
    acos::hal::serial_print("  ProcessLoader: create_process_from_elf called for ");
    acos::hal::serial_print(name ? name : "unknown");
    acos::hal::serial_print("\n");

    scheduler::Process* p = scheduler::Process::create();
    if (!p) {
        acos::hal::serial_print("  ProcessLoader: Process::create failed!\n");
        return nullptr;
    }
    acos::hal::serial_print("  ProcessLoader: Process created, id=");
    acos::hal::serial_print_hex(p->id);
    acos::hal::serial_print("\n");

    u64 entry_point = 0;
    if (elf_data && size > 0) {
        acos::hal::serial_print("  ProcessLoader: loading executable...\n");
        ELFLoadResult load_result = ElfLoader::load_executable(p->address_space, elf_data, size);
        if (!load_result.success) {
            acos::hal::serial_print("  ProcessLoader: ElfLoader::load_executable failed!\n");
            return nullptr;
        }
        entry_point = load_result.entry_point;
        acos::hal::serial_print("  ProcessLoader: load successful, entry=");
        acos::hal::serial_print_hex(entry_point);
        acos::hal::serial_print("\n");

        u64 code_phys = p->address_space->translate(entry_point);
        if (code_phys) {
            acos::hal::serial_print("  ProcessLoader: code at entry: ");
            u8* code_ptr = reinterpret_cast<u8*>(code_phys);
            for (int i = 0; i < 16; i++) {
                acos::hal::serial_print_hex(code_ptr[i]);
                acos::hal::serial_print(" ");
            }
            acos::hal::serial_print("\n");
        }

        u64 ep = entry_point;
        u64 pml4_idx = (ep >> 39) & 0x1FF;
        u64 pdpt_idx = (ep >> 30) & 0x1FF;
        u64 pd_idx   = (ep >> 21) & 0x1FF;
        u64 pt_idx   = (ep >> 12) & 0x1FF;

        u64 pml4_addr = p->address_space->pml4_phys();
        memory::PageTable* pml4 = reinterpret_cast<memory::PageTable*>(pml4_addr);

        acos::hal::serial_print("  ProcessLoader: PML4 Entry: ");
        acos::hal::serial_print_hex(pml4->entries[pml4_idx]);
        acos::hal::serial_print("\n");

        if (pml4->entries[pml4_idx] & 1) {
            memory::PageTable* pdpt = reinterpret_cast<memory::PageTable*>(pml4->entries[pml4_idx] & ~0xFFFULL);
            acos::hal::serial_print("  ProcessLoader: PDPT Entry: ");
            acos::hal::serial_print_hex(pdpt->entries[pdpt_idx]);
            acos::hal::serial_print("\n");

            if (pdpt->entries[pdpt_idx] & 1) {
                memory::PageTable* pd = reinterpret_cast<memory::PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);
                acos::hal::serial_print("  ProcessLoader: PD Entry: ");
                acos::hal::serial_print_hex(pd->entries[pd_idx]);
                acos::hal::serial_print("\n");

                if (pd->entries[pd_idx] & 1) {
                    if (pd->entries[pd_idx] & 0x80) {
                        acos::hal::serial_print("  ProcessLoader: PD is a Huge Page!\n");
                    } else {
                        memory::PageTable* pt = reinterpret_cast<memory::PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);
                        acos::hal::serial_print("  ProcessLoader: PT Entry: ");
                        acos::hal::serial_print_hex(pt->entries[pt_idx]);
                        acos::hal::serial_print("\n");
                    }
                }
            }
        }
    }
    acos::hal::serial_print("  ProcessLoader: allocating stack...\n");
    u64 stack_virt = 0x700000000000;
    const u64 STACK_PAGES = 256; // 1MB stack to support robust user programs and large shells
    for (u64 i = 0; i < STACK_PAGES; ++i) {
        u64 phys = memory::pmm_alloc();
        if (phys) {
            p->address_space->map(stack_virt - (i + 1) * 4096, phys, memory::PageFlags::User | memory::PageFlags::Writable | memory::PageFlags::Present);
        }
    }
    for (u64 i = 0; i < STACK_PAGES; ++i) {
        u64 virt = stack_virt - (i + 1) * 4096;
        u64 translated = p->address_space->translate(virt);
        acos::hal::serial_print("  ProcessLoader: translate stack ");
        acos::hal::serial_print_hex(virt);
        acos::hal::serial_print(" -> ");
        acos::hal::serial_print_hex(translated);
        acos::hal::serial_print("\n");
    }
    acos::hal::serial_print("  ProcessLoader: stack mapped, phys=");
    acos::hal::serial_print_hex(stack_virt);
    acos::hal::serial_print("\n");

    acos::hal::serial_print("  ProcessLoader: creating thread...\n");
    scheduler::Thread* t = scheduler::create_thread(kernel_thread_stub, nullptr);
    if (!t) {
        acos::hal::serial_print("  ProcessLoader: create_thread failed!\n");
        return nullptr;
    }
    t->parent = p;
    t->is_user = true;
    t->entry_point = entry_point;
    p->primary_thread = t;
    acos::hal::serial_print("  ProcessLoader: thread created successfully\n");
    return p;
}
}
