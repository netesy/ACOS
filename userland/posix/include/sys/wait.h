#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#ifdef __cplusplus
}
#endif
