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
    (void)status;
    // Call kernel exit logic
    auto* thr = acos::scheduler::current_thread();
    if (thr) {
        thr->state = acos::scheduler::ThreadState::Terminated;
        acos::scheduler::schedule();
    }
    while(1);
}

int fork(void) {
    // fork() is hard in a microkernel without specific support.
    // We provide a stub for source compatibility.
    errno = ENOSYS;
    return -1;
}

}
