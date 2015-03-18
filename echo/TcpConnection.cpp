#include "TcpConnection.h"
#include <string>
#include <signal.h>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
//这个类用来忽略SIGPIPE信号
class IgnoreSignal
{
    public:
        IgnoreSignal()
        {
            if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
                ERR_EXIT("signal");
        }
};

//当系统系统时，会生成一个全局对象，从而自动注册信号。
IgnoreSignal ignoresignal;

TcpConnection::TcpConnection(int fd, const InetAddress &localAddr, const InetAddress &peerAddr)
    :sockfd_(fd),
     buffer_(fd),
     localAddr_(localAddr),
     peerAddr_(peerAddr)
{}

ssize_t TcpConnection::readn(char *usrbuf, size_t len)
{
     int nread = buffer_.readn(usrbuf, len);
     if(nread == -1)
         ERR_EXIT("readn");
     return nread;
}

ssize_t TcpConnection::writen(const char *usrbuf, size_t len)
{
    int nread = buffer_.writen(usrbuf, len);
    if(nread == -1)
        ERR_EXIT("writen");
    return nread;
}

ssize_t TcpConnection::readLine(char *usrbuf, size_t len)
{
    int nread = buffer_.readLine(usrbuf, len);
    if(nread == -1)
        ERR_EXIT("readLine");
    return nread;
}

string TcpConnection::receive()
{
    char recvbuf[1024] = {0};
    readLine(recvbuf, 1024);
    return string(recvbuf); 
}
void TcpConnection::send(const string &str)
{
    writen(str.c_str(), str.size());
}

void TcpConnection::handleOnlineEvent()
{
    if(onlineCallback_)
        onlineCallback_(shared_from_this());
}

void TcpConnection::handleBuinessEvent()
{
    if(buinessCallback_)
        buinessCallback_(shared_from_this());
}

void TcpConnection::handleCloseEvent()
{
    if(closeCallback_)
        closeCallback_(shared_from_this());
}


