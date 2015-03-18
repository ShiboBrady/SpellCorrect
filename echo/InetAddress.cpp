#include "InetAddress.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

InetAddress::InetAddress(uint16_t port)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = INADDR_ANY;
}

InetAddress InetAddress::getLocalAddress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if(-1 == ::getsockname(sockfd, (struct sockaddr*)&addr, &addrlen))
        ERR_EXIT("getpeername");
    return InetAddress(addr);
}

InetAddress InetAddress::getPeerAddress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if(-1 == ::getpeername(sockfd, (struct sockaddr*)&addr, &addrlen))
        ERR_EXIT("getpeername");
    return InetAddress(addr);
}

