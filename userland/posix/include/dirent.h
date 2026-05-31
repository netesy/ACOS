#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct dirent {
    ino_t  d_ino;
    char   d_name[256];
};

typedef struct {
    int fd;
} DIR;

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

#ifdef __cplusplus
}
#endif
