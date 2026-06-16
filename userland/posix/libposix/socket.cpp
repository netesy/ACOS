#include <acos/process.h>
#include <acos/runtime.h>
#include <sys/socket.h>
#include <errno.h>
#include <acos/process.h>

extern "C" {

int socket(int domain, int type, int protocol) {
    // Map POSIX socket to ACOS socket
    if (domain != AF_INET && domain != AF_INET6) {
        errno = EAFNOSUPPORT;
        return -1;
    }
    
    if (type != SOCK_STREAM && type != SOCK_DGRAM) {
        errno = ESOCKTNOSUPPORT;
        return -1;
    }
    
    // Create socket in kernel
    acos::net::Socket* sock = acos::net::Socket::create(domain, type, protocol);
    if (!sock) {
        errno = ENOMEM;
        return -1;
    }
    
    // Register with process file descriptor table
    acos::scheduler::Process* proc = acos::scheduler::current_thread()->parent;
    if (!proc) {
        errno = ESRCH;
        return -1;
    }
    
    int fd = proc->register_socket(sock);
    return fd;
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
    (void)flags;
    if (!buf || len == 0) {
        errno = EINVAL;
        return -1;
    }
    
    acos::scheduler::Process* proc = acos::scheduler::current_thread()->parent;
    if (!proc) {
        errno = ESRCH;
        return -1;
    }
    
    acos::net::Socket* sock = proc->get_socket(sockfd);
    if (!sock) {
        errno = EBADF;
        return -1;
    }
    
    ssize_t sent = sock->send(buf, len);
    if (sent < 0) {
        errno = EIO;
    }
    
    return sent;
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
    (void)flags;
    if (!buf || len == 0) {
        errno = EINVAL;
        return -1;
    }
    
    acos::scheduler::Process* proc = acos::scheduler::current_thread()->parent;
    if (!proc) {
        errno = ESRCH;
        return -1;
    }
    
    acos::net::Socket* sock = proc->get_socket(sockfd);
    if (!sock) {
        errno = EBADF;
        return -1;
    }
    
    ssize_t received = sock->recv(buf, len);
    if (received < 0) {
        errno = EIO;
    }
    
    return received;
}

}
