#include <pthread.h>
#include <errno.h>
#include <kernel/scheduler/scheduler.h>

extern "C" {

int pthread_create(pthread_t *thread, const void *attr, void *(*start_routine) (void *), void *arg) {
    if (!thread || !start_routine) return EINVAL;
    
    // Create ACOS thread
    acos::scheduler::Thread* t = acos::scheduler::create_thread(
        reinterpret_cast<acos::scheduler::ThreadEntry>(start_routine),
        arg
    );
    
    if (!t) return ENOMEM;
    
    // Store thread ID in pthread_t
    *thread = (pthread_t)t->id;
    
    // Wake thread to start execution
    acos::scheduler::wake_thread(t);
    
    return 0;
}

int pthread_join(pthread_t thread, void **retval) {
    if (thread == 0) return EINVAL;
    
    // Find thread by ID
    acos::scheduler::Thread* t = acos::scheduler::find_thread((u64)thread);
    if (!t) return ESRCH;
    
    // Wait for thread to terminate
    while (t->state != acos::scheduler::ThreadState::Terminated) {
        acos::scheduler::schedule();
    }
    
    // Get return value if requested
    if (retval) {
        *retval = t->return_value;
    }
    
    return 0;
}

}
