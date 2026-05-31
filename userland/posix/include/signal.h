#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SIGHUP     1
#define SIGINT     2
#define SIGQUIT    3
#define SIGILL     4
#define SIGTRAP    5
#define SIGABRT    6
#define SIGBUS     7
#define SIGFPE     8
#define SIGKILL    9
#define SIGUSR1   10
#define SIGSEGV   11
#define SIGUSR2   12
#define SIGPIPE   13
#define SIGALRM   14
#define SIGTERM   15

typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
int kill(pid_t pid, int sig);

#ifdef __cplusplus
}
#endif
