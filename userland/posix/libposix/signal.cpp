#include <signal.h>
#include <errno.h>
#include <kernel/scheduler/scheduler.h>

extern "C" {

sighandler_t signal(int signum, sighandler_t handler) {
    if (signum < 1 || signum > 64) {
        errno = EINVAL;
        return (sighandler_t)-1;
    }
    
    // Get current thread
    acos::scheduler::Thread* thread = acos::scheduler::current_thread();
    if (!thread) {
        errno = ESRCH;
        return (sighandler_t)-1;
    }
    
    (void)handler;
    errno = ENOSYS;
    return (sighandler_t)-1;
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
    acos::scheduler::Process* proc = acos::scheduler::find_process((acos::u64)pid);
    if (!proc) {
        errno = ESRCH;
        return -1;
    }
    
    (void)sig;
    errno = ENOSYS;
    return -1;
}

}
