#include <sys/time.h>
#include <errno.h>

extern "C" {

int gettimeofday(struct timeval *tv, void *tz) {
    (void)tz;
    if (tv) {
        tv->tv_sec = 0; // Get from kernel
        tv->tv_usec = 0;
    }
    return 0;
}

}
