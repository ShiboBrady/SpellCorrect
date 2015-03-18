#ifndef TCPCONNECTION
#define TCPCONNECTION 
#include "NonCopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Rio.h"
#include <string>
#include <memory>
#include <functional>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : NonCopyable,
                      public std::enable_shared_from_this<TcpConnection>
{
    public:
        typedef std::function<void (TcpConnectionPtr)> TcpConnectionCallback;
        TcpConnection(int fd, const InetAddress &localaddr, const InetAddress &peeraddr);
        ~TcpConnection() {shutdown(); }

        int getFd() {return sockfd_.getFd(); };
        void shutdown() {sockfd_.shutdown(); };

        ssize_t readn(char *usrbuf, size_t len);
        ssize_t writen(const char *usrbuf, size_t len);
        ssize_t readLine(char *usrbuf, size_t len);

        std::string receive();
        void send(const std::string &s);

        void setOnlineCallback(const TcpConnectionCallback &cb)
        { onlineCallback_ = cb; }
        void setBuinessCallback(const TcpConnectionCallback &cb)
        { buinessCallback_ = cb; }
        void setCloseCallback(const TcpConnectionCallback &cb)
        { closeCallback_ = cb; }

        void handleOnlineEvent();
        void handleBuinessEvent();
        void handleCloseEvent();

        const InetAddress &getLocalAddr() const
        { return localAddr_; }
        const InetAddress &getPeerAddr() const
        { return peerAddr_; }

    private:
        Socket sockfd_;
        Rio buffer_;

        InetAddress localAddr_;
        InetAddress peerAddr_;

        TcpConnectionCallback onlineCallback_;
        TcpConnectionCallback buinessCallback_;
        TcpConnectionCallback closeCallback_;
};


#endif  /*TCPCONNECTION*/
