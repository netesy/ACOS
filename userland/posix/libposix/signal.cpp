#include <signal.h>
#include <errno.h>

extern "C" {

sighandler_t signal(int signum, sighandler_t handler) {
    if (signum < 1 || signum > 64) {
        errno = EINVAL;
        return SIG_ERR;
    }
    
    // Get current thread
    acos::scheduler::Thread* thread = acos::scheduler::current_thread();
    if (!thread) {
        errno = ESRCH;
        return SIG_ERR;
    }
    
    // Store old handler
    sighandler_t old_handler = thread->signal_handlers[signum];
    
    // Set new handler
    thread->signal_handlers[signum] = handler;
    
    return old_handler;
}

int kill(pid_t pid, int sig) {
    if (sig < 0 || sig > 64) {
        errno = EINVAL;
        return -1;
    }
    
    if (pid <= 0) {
        errno = EINVAL;
        return -1;
    }
    
    // Find process by PID
    acos::scheduler::Process* proc = acos::scheduler::find_process(pid);
    if (!proc) {
        errno = ESRCH;
        return -1;
    }
    
    // Send signal to all threads in process
    for (usize i = 0; i < proc->thread_count; i++) {
        acos::scheduler::Thread* thread = proc->threads[i];
        if (thread) {
            thread->pending_signals |= (1ULL << sig);
        }
    }
    
    return 0;
}

}
