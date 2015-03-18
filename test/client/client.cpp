#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include "Rio.h"


int main(int argc, const char *argv[])
{
    int peerfd;
    if(-1 == (peerfd = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    bzero(&client_addr, addrlen);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9999);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == connect(peerfd, (struct sockaddr*)&client_addr, addrlen))
        ERR_EXIT("connect");
    struct pollfd events[2];
    events[0].fd = peerfd;
    events[0].events = POLLIN;
    events[1].fd = STDIN_FILENO;
    events[1].events = POLLIN;
    int nready;
    char buf[1024] = {0};
    rio_t rio;
    rio_init(&rio, peerfd);
    while(1){
        nready = poll(events, 2, -1);
        if(events[0].revents & POLLIN){
            rio_readline(&rio, buf, 1024);
            printf("%s", buf);
        }else if(events[1].revents & POLLIN){
            if(fgets(buf, 1024, stdin) == NULL)
                break;
            write(peerfd, buf, strlen(buf));
        }
    }
    return 0;
}


