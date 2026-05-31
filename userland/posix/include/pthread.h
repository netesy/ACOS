#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef acos::u64 pthread_t;

struct pthread_mutex_t {
    acos::u64 handle;
};

struct pthread_cond_t {
    acos::u64 handle;
};

int pthread_create(pthread_t *thread, const void *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
void pthread_exit(void *retval);

int pthread_mutex_init(pthread_mutex_t *mutex, const void *attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#ifdef __cplusplus
}
#endif
