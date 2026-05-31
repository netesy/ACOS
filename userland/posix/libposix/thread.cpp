#include <pthread.h>
#include <errno.h>
#include <kernel/scheduler/scheduler.h>

extern "C" {

int pthread_create(pthread_t *thread, const void *attr, void *(*start_routine) (void *), void *arg) {
    (void)attr;
    // Map to ACOS thread creation
    // acos::scheduler::create_thread(...)
    (void)thread; (void)start_routine; (void)arg;
    return 0;
}

int pthread_join(pthread_t thread, void **retval) {
    (void)thread; (void)retval;
    return 0;
}

}
