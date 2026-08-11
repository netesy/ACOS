#include <kernel/scheduler/scheduler.h>
#include <kernel/smp/cpu.h>
#include <kernel/hal/spinlock.h>
#include <kernel/hal/serial.h>
#include <kernel/hal/gdt.h>
#include <kernel/memory/heap.h>
#include <acos/types.h>

namespace acos::scheduler {

static bool g_has_xsave = false;
static bool g_has_avx = false;

static RunQueue g_run_queues[64];
static hal::SpinLock g_queue_locks[64];

// Thread blocked on console I/O (polled from idle loop)
static Thread* g_console_blocked_thread = nullptr;

void set_console_blocked(Thread* thread) {
    g_console_blocked_thread = thread;
}

void clear_console_blocked(Thread* thread) {
    if (g_console_blocked_thread == thread) {
        g_console_blocked_thread = nullptr;
    }
}

Thread* get_console_blocked() {
    return g_console_blocked_thread;
}

// Make g_run_queues accessible for global functions
RunQueue* get_run_queues() {
    return g_run_queues;
}

void reap_zombies() {
    smp::CpuData* cpu = smp::Cpu::current();
    if (cpu && cpu->thread_to_reap) {
        Thread* t = cpu->thread_to_reap;
        cpu->thread_to_reap = nullptr;

        // Free stack allocation safely
        if (t->stack_top) {
            u64 stack_base = t->stack_top - 16384;
            acos::memory::kfree(reinterpret_cast<void*>(stack_base));
        }

        // Free the Thread structure itself
        acos::memory::kfree(t);
    }
}

void scheduler_init() {
    for (int i = 0; i < 64; i++) {
        g_run_queues[i].head = nullptr;
        g_run_queues[i].tail = nullptr;
        g_run_queues[i].count = 0;
    }

    // Detect FPU/SSE/AVX capabilities via CPUID
    u32 eax = 0, ebx = 0, ecx = 0, edx = 0;
    __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(1));

    g_has_xsave = (ecx & (1ULL << 26)) != 0;
    g_has_avx = (ecx & (1ULL << 28)) != 0;

    if (g_has_xsave) {
        // Enable OSXSAVE in CR4 (bit 18)
        u64 cr4;
        __asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
        cr4 |= (1ULL << 18);
        __asm__ volatile("mov %0, %%cr4" : : "r"(cr4));

        // Set XCR0 register to enable x87 (bit 0), SSE (bit 1)
        u64 xcr0 = 3;
        if (g_has_avx) {
            xcr0 |= 4; // Enable AVX (bit 2)
        }

        u32 low = xcr0 & 0xFFFFFFFF;
        u32 high = (xcr0 >> 32) & 0xFFFFFFFF;
        __asm__ volatile("xsetbv" : : "c"(0), "a"(low), "d"(high));

        acos::hal::serial_print("[FPU] XSAVE and AVX context management enabled.\n");
    } else {
        acos::hal::serial_print("[FPU] Legacy FXSAVE/FXRSTOR context management enabled.\n");
    }
}

static void enqueue_thread_internal(u32 cpu_id, Thread* thread) {
    if (!g_run_queues[cpu_id].head) {
        g_run_queues[cpu_id].head = thread;
    } else {
        g_run_queues[cpu_id].tail->next = thread;
    }
    g_run_queues[cpu_id].tail = thread;
    thread->next = nullptr;
    g_run_queues[cpu_id].count++;
}

void enqueue_thread(u32 cpu_id, Thread* thread) {
    hal::ScopedLock lock(g_queue_locks[cpu_id]);
    enqueue_thread_internal(cpu_id, thread);
}

void schedule() {
    reap_zombies();

    u32 cpu_id = smp::Cpu::id();

    g_queue_locks[cpu_id].lock();
    
    smp::CpuData* cpu = smp::Cpu::current();
    if (!cpu) {
        g_queue_locks[cpu_id].unlock();
        return;
    }
    
    // Get next thread from run queue
    Thread* next = g_run_queues[cpu_id].head;
    while (next && next->state == ThreadState::Terminated) {
        // Enqueue next directly into cpu->thread_to_reap
        // If there's already one, reap it first
        if (cpu->thread_to_reap) {
            Thread* t = cpu->thread_to_reap;
            cpu->thread_to_reap = nullptr;
            if (t->stack_top) {
                u64 stack_base = t->stack_top - 16384;
                acos::memory::kfree(reinterpret_cast<void*>(stack_base));
            }
            acos::memory::kfree(t);
        }
        cpu->thread_to_reap = next;

        // Pop from ready queue
        g_run_queues[cpu_id].head = next->next;
        if (!g_run_queues[cpu_id].head) {
            g_run_queues[cpu_id].tail = nullptr;
        }
        g_run_queues[cpu_id].count--;

        next = g_run_queues[cpu_id].head;
    }

    if (!next) {
        // No runnable threads — release lock and return.
        // Caller (idle loop) should hlt to avoid spinning.
        g_queue_locks[cpu_id].unlock();
        return;
    }
    
    // Remove from queue
    g_run_queues[cpu_id].head = next->next;
    if (!g_run_queues[cpu_id].head) {
        g_run_queues[cpu_id].tail = nullptr;
    }
    g_run_queues[cpu_id].count--;
    
    // Get current thread
    Thread* current = cpu->current_thread;
    
    // If current thread is still runnable, re-enqueue it
    if (current && current->state == ThreadState::Running) {
        current->state = ThreadState::Ready;
        enqueue_thread_internal(cpu_id, current);
    }
    // Blocked/Terminated threads are NOT re-enqueued — that's the
    // whole point of proper blocking.
    
    // Switch to next thread
    if (next != current) {
        acos::hal::serial_print("[SCHED] Switching from thread ");
        acos::hal::serial_print_hex(current ? current->id : 0);
        acos::hal::serial_print(" (is_user=");
        acos::hal::serial_print_hex(current ? current->is_user : 0);
        acos::hal::serial_print(") to thread ");
        acos::hal::serial_print_hex(next->id);
        acos::hal::serial_print(" (is_user=");
        acos::hal::serial_print_hex(next->is_user);
        acos::hal::serial_print(")\n");

        next->state = ThreadState::Running;
        cpu->current_thread = next;
        
        // Update TSS RSP0 and per-CPU kernel_rsp for user->kernel transition
        hal::tss_set_rsp0(next->stack_top);
        cpu->kernel_rsp = next->stack_top;

        // Switch page table (CR3) to the target thread's process address space
        if (next->parent && next->parent->address_space) {
            __asm__ volatile("mov %0, %%cr3" : : "r"(next->parent->address_space->pml4_phys()));
        }

        // If the current thread has terminated, schedule it for deferred reaping
        if (current && current->state == ThreadState::Terminated) {
            if (cpu->thread_to_reap) {
                Thread* t = cpu->thread_to_reap;
                cpu->thread_to_reap = nullptr;
                if (t->stack_top) {
                    u64 stack_base = t->stack_top - 16384;
                    acos::memory::kfree(reinterpret_cast<void*>(stack_base));
                }
                acos::memory::kfree(t);
            }
            cpu->thread_to_reap = current;
        }

        // Release lock before context switch to avoid deadlock
        g_queue_locks[cpu_id].unlock();

        // Perform context switch
        if (current) {
            if (g_has_xsave) {
                __asm__ volatile("xsave %0" : "=m"(current->fpu_state) : "a"(0xFFFFFFFF), "d"(0xFFFFFFFF));
                __asm__ volatile("xrstor %0" : : "m"(next->fpu_state), "a"(0xFFFFFFFF), "d"(0xFFFFFFFF));
            } else {
                __asm__ volatile("fxsave %0" : "=m"(current->fpu_state));
                __asm__ volatile("fxrstor %0" : : "m"(next->fpu_state));
            }
            context_switch(&current->stack_pointer, next->stack_pointer);
        } else {
            // First thread on this CPU
            if (g_has_xsave) {
                __asm__ volatile("xrstor %0" : : "m"(next->fpu_state), "a"(0xFFFFFFFF), "d"(0xFFFFFFFF));
            } else {
                __asm__ volatile("fxrstor %0" : : "m"(next->fpu_state));
            }
            __asm__ volatile("mov %0, %%rsp" : : "r"(next->stack_pointer));
        }
    } else {
        g_queue_locks[cpu_id].unlock();
    }
}

Thread* current_thread() {
    return smp::Cpu::current()->current_thread;
}

void wake_thread(Thread* thread) {
    if (!thread) return;
    // Mark thread as ready to run before enqueueing
    thread->state = ThreadState::Ready;
    enqueue_thread(0, thread);
}

void block_thread(Thread* thread) {
    if (!thread) return;
    // Mark thread as blocked — schedule() will NOT re-enqueue it.
    // The thread stays off the run queue until wake_thread() is called.
    thread->state = ThreadState::Blocked;
    schedule();
    // Execution resumes here after wake_thread() + context switch back.
}

usize get_thread_count() {
    usize total = 0;
    RunQueue* queues = get_run_queues();
    for (int i = 0; i < 64; i++) {
        total += queues[i].count;
    }
    return total;
}

usize get_running_thread_count() {
    return get_thread_count();
}


// Thread creation - allocate and initialize a new thread
Thread* create_thread(ThreadEntry entry, void* arg) {
    // acos::hal::serial_print("[SCHED] Creating thread...\n");
    // Allocate thread structure
    Thread* thread = (Thread*)acos::memory::kmalloc(sizeof(Thread));
    if (!thread) return nullptr;
    
    // Initialize thread
    static u64 next_thread_id = 1;
    thread->id = next_thread_id++;
    thread->state = ThreadState::Created;
    thread->parent = nullptr;
    thread->is_user = false;
    thread->return_value = nullptr;
    thread->next = nullptr;
    thread->entry_point = (u64)entry;
    thread->arg = arg;

    // Initialize FPU/SSE state to safe hardware defaults without corrupting the caller's CPU FPU state
    for (int i = 0; i < 512; i++) {
        thread->fpu_state[i] = 0;
    }
    *reinterpret_cast<u16*>(&thread->fpu_state[0]) = 0x037F; // FCW: default x87 control word
    *reinterpret_cast<u32*>(&thread->fpu_state[24]) = 0x1F80; // MXCSR: default SSE control/status (masks exceptions)
    
    // Allocate stack (16KB)
    const usize STACK_SIZE = 16384;
    u64* stack = (u64*)acos::memory::kmalloc(STACK_SIZE);
    if (!stack) {
        acos::memory::kfree(thread);
        return nullptr;
    }
    
    thread->stack_top = (u64)stack + STACK_SIZE;
    thread->stack_pointer = thread->stack_top;
    
    // Setup initial stack frame for thread entry
    // The stack must be compatible with context_switch in switch.S
    // context_switch pops: rbp, rbx, r12, r13, r14, r15, then ret

    // According to x86_64 SysV ABI, the stack must be 16-byte aligned
    // at the moment 'call' is executed. This means after 'ret' pops
    // the entry point, rsp must be 16-byte aligned.

    // Initial STACK_TOP is 16-byte aligned by kmalloc usually,
    // but let's be explicit.
    thread->stack_pointer &= ~0xFULL;

    // 1. ABI Alignment Padding (8 bytes)
    // Pushing entry (8) + 6 regs (48) = 56 bytes.
    // 56 % 16 = 8. So we need 8 bytes padding to make total 64 (divisible by 16).
    thread->stack_pointer -= sizeof(u64);
    *(u64*)thread->stack_pointer = 0;

    // 2. Entry point (popped by ret)
    thread->stack_pointer -= sizeof(u64);
    *(u64*)thread->stack_pointer = (u64)entry;
    
    // 3. Callee-saved registers (rbp, rbx, r12, r13, r14, r15)
    // These 6 registers are popped by context_switch
    for (int i = 0; i < 6; i++) {
        thread->stack_pointer -= sizeof(u64);
        *(u64*)thread->stack_pointer = 0;
    }

    // Note: We are currently ignoring the 'arg' in the generic create_thread
    // because x86_64 ABI passes first arg in RDI.
    // To support arg, we would need to initialize RDI on the stack and
    // have context_switch or a wrapper restore it.
    (void)arg;
    
    return thread;
}

// Find thread by ID
Thread* find_thread(u64 thread_id) {
    // Search all run queues
    RunQueue* queues = get_run_queues();
    for (int cpu = 0; cpu < 64; cpu++) {
        Thread* t = queues[cpu].head;
        while (t) {
            if (t->id == thread_id) return t;
            t = t->next;
        }
    }
    return nullptr;
}

// Find process by ID in the kernel process table
Process* find_process(u64 process_id) {
    return process_table_find(process_id);
}

struct SleepEntry {
    Thread* thread;
    u64 target_tsc;
};

static SleepEntry g_sleep_queue[128];
static usize g_sleep_count = 0;
static hal::SpinLock g_sleep_lock;

void register_sleep(Thread* thread, u64 ms) {
    if (!thread) return;
    hal::ScopedLock lock(g_sleep_lock);
    if (g_sleep_count < 128) {
        // 2.5 GHz TSC estimate
        u64 target_tsc = __builtin_ia32_rdtsc() + ms * 2500000;
        g_sleep_queue[g_sleep_count++] = { thread, target_tsc };
    }
}

void check_sleeping_threads() {
    hal::ScopedLock lock(g_sleep_lock);
    u64 current_tsc = __builtin_ia32_rdtsc();
    for (usize i = 0; i < g_sleep_count; ) {
        if (current_tsc >= g_sleep_queue[i].target_tsc) {
            Thread* t = g_sleep_queue[i].thread;
            g_sleep_queue[i] = g_sleep_queue[--g_sleep_count];
            wake_thread(t);
        } else {
            i++;
        }
    }
}

usize get_sleep_count() {
    hal::ScopedLock lock(g_sleep_lock);
    return g_sleep_count;
}

} // namespace acos::scheduler
