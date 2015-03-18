#ifndef POLLPOLLER_H
#define POLLPOLLER_H 
#include "NonCopyable.h"
#include "TcpConnection.h"
#include <poll.h>
#include <functional>
#include <map>

class PollPoller : NonCopyable
{
    public:
        typedef TcpConnection::TcpConnectionCallback PollerCallback;
        typedef std::map<int, TcpConnectionPtr>::iterator TcpIterator;
        PollPoller(int fd);
        ~PollPoller();

        void wait();
        void handle();
        void handle_accept();
        void handle_data();

        void handleOnlineEvents(int fd);
        void handleBussinessEvents(int fd);
        void handleCloseEvents(int i);

        void setOnlineCallback(const PollerCallback &cb)
        { onlineCallback_ = cb; }
        void setBussinessCallback(const PollerCallback &cb)
        { bussinessCallback_ = cb; }
        void setCloseCallback(const PollerCallback &cb)
        { closeCallback_ = cb; }

    private:
        int listenfd_;
        int nready_;
        int maxi_;
        struct pollfd events_[2048];
        std::map<int, TcpConnectionPtr> conn_;

        PollerCallback onlineCallback_;
        PollerCallback bussinessCallback_;
        PollerCallback closeCallback_;
};  

#endif  /*POLLPOLLER_H*/
