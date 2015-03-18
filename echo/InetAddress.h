#ifndef INETADDRESS_H
#define INETADDRESS_H 
#include "Copyable.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

class InetAddress : Copyable
{
    public:
        explicit InetAddress(uint16_t port);
        InetAddress(const struct sockaddr_in &addr):addr_(addr) {}

        struct sockaddr_in &getInetAddress() {return addr_; }
        void setInetAddress(const struct sockaddr_in &addr) {addr_ = addr; }
        
        uint32_t ipNetEndian() const {return addr_.sin_addr.s_addr; }
        uint16_t portNetEndian() const {return addr_.sin_port; }

        char * getIp() const {return ::inet_ntoa(addr_.sin_addr); }
        uint16_t getPort() const {return ntohs(addr_.sin_port); }

        static InetAddress getLocalAddress(int sockfd);
        static InetAddress getPeerAddress(int sockfd);
    private:
        struct sockaddr_in addr_;
};

#endif  /*INETADDRESS_H*/
