#ifndef SERVER_H
#define SERVER_H 

#include "TextQuery.h"
#include "CacheManager.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "NonCopyable.h"
#include "Log.h"
#include "GetConfig.h"
#include <string>
#include <vector>

class Server : NonCopyable
{
    public:
        //Server(int port, const std::string &enStorageFile, const std::string &chStorageFile, const std::string &cacheFile, const std::string &logFile);
        Server(GetConfig *config);
        ~Server();
        void start();

    private:
        void onlineCallback(const TcpConnectionPtr &conn);
        void bussinessCallback(const TcpConnectionPtr &conn);
        void closeCallback(const TcpConnectionPtr &conn);
        void computer(const std::string &word, Cache *cache, const TcpConnectionPtr &conn);

        TcpServer server_;
        TextQuery search_;
        CacheManager caches_;
        Threadpool pool_;
        Log log_;
};

#endif  /*SERVER_H*/
