#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AF_INET     2
#define AF_INET6    10
#define SOCK_STREAM 1
#define SOCK_DGRAM  2

struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};

int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, acos::u32 addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, acos::u32 *addrlen);
int connect(int sockfd, const struct sockaddr *addr, acos::u32 addrlen);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

#ifdef __cplusplus
}
#endif
