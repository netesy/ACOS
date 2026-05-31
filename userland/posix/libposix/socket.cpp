#include <sys/socket.h>
#include <errno.h>
#include <kernel/net/socket.h>

extern "C" {

int socket(int domain, int type, int protocol) {
    (void)domain; (void)type; (void)protocol;
    // Map to acos::net::Socket
    return 0;
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
    (void)sockfd; (void)buf; (void)len; (void)flags;
    return 0;
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
    (void)sockfd; (void)buf; (void)len; (void)flags;
    return 0;
}

}
