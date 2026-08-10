#pragma once

typedef long time_t;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

#ifdef __cplusplus
extern "C" {
#endif

static inline time_t time(time_t* t) {
    if (t) *t = 0;
    return 0;
}

static inline struct tm* localtime(const time_t* t) {
    static struct tm dummy_tm = {0, 0, 0, 1, 0, 100, 0, 0, 0};
    (void)t;
    return &dummy_tm;
}

static inline time_t mktime(struct tm* t) {
    (void)t;
    return 0;
}

#ifdef __cplusplus
}
#endif
