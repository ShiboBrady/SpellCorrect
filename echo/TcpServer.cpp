#include "TcpServer.h"
#include "InetAddress.h"
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

TcpServer::TcpServer(int port)
{
    int listenfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");
    socket_.reset(new Socket(listenfd));
    socket_->setsockopt();
    socket_->bind(InetAddress(port).getInetAddress());
    socket_->listen();
    poll_.reset(new PollPoller(socket_->getFd()));
}


void TcpServer::start()
{
    poll_->setOnlineCallback(onlineCallback_);
    poll_->setBussinessCallback(bussinessCallback_);
    poll_->setCloseCallback(closeCallback_);
    while(1){
        poll_->wait();
        poll_->handle();
    } 
}
