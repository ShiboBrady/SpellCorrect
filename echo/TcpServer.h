#ifndef TCP_SERVER_H
#define TCP_SERVER_H 
#include "NonCopyable.h"
#include "PollPoller.h"
#include "Socket.h"
#include <memory>

class TcpServer : NonCopyable
{
    public:
        typedef PollPoller::PollerCallback TcpServerCallback;
        TcpServer(int port);
        void start();

        void setOnlineCallback(const TcpServerCallback &cb)
        { onlineCallback_ = cb; }
        void setBussinessCallback(const TcpServerCallback &cb)
        { bussinessCallback_ = cb; }
        void setCloseCallback(const TcpServerCallback &cb)
        { closeCallback_ = cb; }

    private:
        std::shared_ptr<PollPoller> poll_; 
        std::shared_ptr<Socket> socket_;

        TcpServerCallback onlineCallback_;
        TcpServerCallback bussinessCallback_;
        TcpServerCallback closeCallback_;
};

#endif  /*TCP_SERVER_H*/
