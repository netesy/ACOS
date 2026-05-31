#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct timeval {
    time_t      tv_sec;
    acos::u64   tv_usec;
};

int gettimeofday(struct timeval *tv, void *tz);

#ifdef __cplusplus
}
#endif
