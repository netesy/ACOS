#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>

extern "C" {

pid_t getpid(void) {
    auto* thr = acos::scheduler::current_thread();
    if (thr && thr->parent) return thr->parent->id;
    return 0;
}

void _exit(int status) {
    // Terminate current thread and process
    acos::scheduler::Thread* thr = acos::scheduler::current_thread();
    if (!thr) {
        while(1) __asm__("hlt");
    }
    
    acos::scheduler::Process* proc = thr->parent;
    if (proc) {
        // Mark all threads as terminated
        for (usize i = 0; i < proc->thread_count; i++) {
            if (proc->threads[i]) {
                proc->threads[i]->state = acos::scheduler::ThreadState::Terminated;
                proc->threads[i]->return_value = (void*)(uintptr_t)status;
            }
        }
        
        // Mark process as terminated
        proc->state = acos::scheduler::ProcessState::Terminated;
        proc->exit_code = status;
    }
    
    // Reschedule to next thread
    acos::scheduler::schedule();
    
    // Should never reach here
    while(1) __asm__("hlt");
}

int fork(void) {
    // fork() is hard in a microkernel without specific support.
    // We provide a stub for source compatibility.
    errno = ENOSYS;
    return -1;
}

}
