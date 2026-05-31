#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int fork(void);
int execve(const char *pathname, char *const argv[], char *const envp[]);
void _exit(int status);

pid_t getpid(void);
pid_t getppid(void);

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
off_t lseek(int fd, off_t offset, int whence);

int unlink(const char *pathname);
int rmdir(const char *pathname);

unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif
