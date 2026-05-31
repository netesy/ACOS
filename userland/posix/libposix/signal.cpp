#include <signal.h>
#include <errno.h>

extern "C" {

sighandler_t signal(int signum, sighandler_t handler) {
    (void)signum; (void)handler;
    return nullptr;
}

int kill(pid_t pid, int sig) {
    (void)pid; (void)sig;
    return 0;
}

}
