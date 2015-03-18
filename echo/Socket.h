#ifndef SOCKET_H
#define SOCKET_H 
#include "Copyable.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket : Copyable
{
    public:
        explicit Socket(int fd):fd_(fd){}
        void setsockopt();
        void bind(struct sockaddr_in &addr);
        void listen();
        int accept();
        void setFd(int fd) {fd_ = fd; }
        int getFd() {return fd_; }
        void shutdown(){::shutdown(fd_, SHUT_WR); }
    private:
        int fd_;
};

#endif  /*SOCKET_H*/
