#include "Socket.h"
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void Socket::setsockopt()
{
    int reuse = 1;
    if(-1 == ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, static_cast<socklen_t>(sizeof(reuse)))) 
        ERR_EXIT("setsockopt");
}

void Socket::bind(struct sockaddr_in &addr)
{
    if(-1 == ::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)))
        ERR_EXIT("bind");
}

void Socket::listen()
{
    if(-1 == ::listen(fd_, SOMAXCONN))
        ERR_EXIT("listen");
}

int Socket::accept()
{
    int fd_client;
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    if(-1 == (fd_client = ::accept(fd_, (struct sockaddr*)&client_addr, &addrlen)))
        ERR_EXIT("accept");
    return fd_client;
}


