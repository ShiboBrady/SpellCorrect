#include "Server.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
using namespace std::placeholders;

Server::Server(GetConfig *config)
    //服务器模块初始化
    :server_(config->getPort()),
    //查询模块初始化
     search_(config->getEnStorageFile(), config->getChStorageFile()),
     //缓存模块初始化
     caches_(config->getCacheFile(), config->getCacheNum(), config->getUpdateFrequence()),
     //线程池模块初始化
     pool_(1000, config->getCacheNum()),
     //日志模块初始化
     log_(config->getLogFile())
{
    server_.setOnlineCallback(bind(&Server::onlineCallback, this, _1));
    server_.setBussinessCallback(bind(&Server::bussinessCallback, this, _1));
    server_.setCloseCallback(bind(&Server::closeCallback, this, _1));
}

Server::~Server()
{
    pool_.stop();
    log_.stop();
    caches_.stop();
}

void Server::start()
{
    caches_.start(); //缓存池启动
    pool_.start(); //线程池启动
    server_.start(); //服务器启动
    log_.addLog("Server is start.\n");
}

void Server::onlineCallback(const TcpConnectionPtr &conn)
{
    ostringstream oss;
    oss << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is online." << endl;
    string logmsg = oss.str();
    cout << logmsg;
    log_.addLog(logmsg);
    conn->send("Input a word to query.\r\n");
}

void Server::bussinessCallback(const TcpConnectionPtr &conn)
{
    string word = conn->receive();
    cout << "recv: " << word << endl;
    cout << "size: " << word.size() << endl;
    //给线程池增加一条任务，并分配一个Cache块
    pool_.add_task(bind(&Server::computer, this, word, caches_.getCache(), conn));
}

void Server::closeCallback(const TcpConnectionPtr &conn)
{ 
    ostringstream oss;
    oss << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is offline." << endl;
    string logmsg = oss.str();
    cout << logmsg;
    log_.addLog(logmsg);
}

void Server::computer(const string &usrword, Cache *cache, const TcpConnectionPtr &conn)
{
    ostringstream oss;
    oss << "get " << cache->getOrder() << " cache." << endl;
    log_.addLog(oss.str());
    oss.str("");
    string word = usrword;
    //去掉字符串后面的换行符
    tools::trimSpace(word);
    //从Cache中查找
    map<string, string>::iterator it = cache->getCache().find(word);
    //Cache中有时直接返回
    if(it != cache->getCache().end()){
        conn->send(it->second + "\n");
        caches_.returnCache(cache->getOrder());
        oss << "Search from cache: " << word << " -> " << it->second << endl;
        log_.addLog(oss.str());
        oss.str("");
    }//词库中没有时从词库中查找
    else{
        string result = search_.query(word);
        //如果用户输入的词在词库中不存在，就插入到Cache中
        if(result != word){
            cache->getCache().insert(make_pair(word, result));
            oss << "One pair is add to cache: " << word << " -> " << result << endl;
            log_.addLog(oss.str());
            oss.str("");
        }
        //归还这个Cache块
        caches_.returnCache(cache->getOrder());
        //result += "\n";
        conn->send(result + "\n");
    }
}

