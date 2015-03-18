#include "PollPoller.h"
#include "InetAddress.h"
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

using namespace std;

PollPoller::PollPoller(int fd)
    :listenfd_(fd)
{
     for(int i = 0; i < 2048; ++i)
         events_[i].fd = -1;
     events_[0].fd = listenfd_;
     events_[0].events = POLLIN;
     maxi_ = 0;
     nready_ = 0;
}

PollPoller::~PollPoller()
{
    close(listenfd_); 
}

void PollPoller::wait()
{
    do{
        nready_ = ::poll(events_, maxi_ + 1, -1);
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        ERR_EXIT("poll");
}

void PollPoller::handle()
{
    handle_accept();
    handle_data();
}

void PollPoller::handle_accept()
{
    if(events_[0].revents & POLLIN){
        int peerfd = ::accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accpet");
        handleOnlineEvents(peerfd);
        --nready_;
    }
}

void PollPoller::handle_data()
{
    for(int i = 1; i <= maxi_; ++i){
        if(nready_ == 0)
            break;
        int fd = events_[i].fd;
        if(fd != -1 && (events_[i].revents & POLLIN)){
            char recvbuf[1024];
            int nread = recv(fd, recvbuf, 1024, MSG_PEEK);
            if(nread == -1)
                ERR_EXIT("recv");
            else if(nread == 0){
                handleCloseEvents(i);
                --nready_;
                continue;
            }
            handleBussinessEvents(fd);
            --nready_;
        }
    }
}

void PollPoller::handleOnlineEvents(int fd)
{
    //增加fd到poll
    //增加tcpconnection到map
    //调用callback
    int i;
    for(i = 1; i < 2048; ++i)
        if(events_[i].fd == -1){
            events_[i].fd = fd;
            events_[i].events = POLLIN;
            if(maxi_ < i)
                maxi_ = i;
            break;
        }
    if(i == 2048)
        ERR_EXIT("Too much clients.");

    TcpConnectionPtr conn(new TcpConnection(fd,
                          InetAddress::getLocalAddress(fd),
                          InetAddress::getPeerAddress(fd)));
    conn->setOnlineCallback(onlineCallback_);
    conn->setBuinessCallback(bussinessCallback_);
    conn->setCloseCallback(closeCallback_);

    pair<TcpIterator, bool> result = conn_.insert(make_pair(fd, conn));
    assert(result.second == true);
    //onlineCallback_(conn);
    conn->handleOnlineEvent();
}

void PollPoller::handleBussinessEvents(int fd)
{
    //查找map
    //调用callback
    TcpIterator result = conn_.find(fd);
    assert(result != conn_.end());
    //messageCallback_(result->second);
    result->second->handleBuinessEvent();
}

void PollPoller::handleCloseEvents(int i)
{
    //从poll中删除fd
    //从map中删除fd
    //调用callback
    int fd = events_[i].fd;
    events_[i].fd = -1;
    TcpIterator result = conn_.find(fd);
    assert(result != conn_.end());
    //closeCallback_(result->second);
    result->second->handleCloseEvent();
    //cout << "One client is offline." << endl;
    //cout << "Client " << result->second->getPeerAddr().getIp() << ":" << result->second->getPeerAddr().getPort() << " is offline." << endl;
    conn_.erase(result);
}
