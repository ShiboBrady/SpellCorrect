#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H 

#include "Cache.h"
#include "Queue.hpp"
#include "Mutex.h"
#include "Cond.h"
#include "ThreadTimer.h"
#include <vector>
#include <string>

class CacheManager
{
    public:
        CacheManager(const std::string &cachefile, size_t cacheNum, int updateFrequece);
        ~CacheManager();
        void start();
        void stop();
        Cache *getCache();
        void returnCache(size_t i);
        void writeToFile();
        void updateCache();
    private:
        std::string cachefile_;
        size_t cacheNum_;
        std::vector<Cache> caches_; //Cache池的数据结构
        Cache totalCache_; //汇总所有Cache块信息的Cache块
        std::vector<size_t> flags_; //用来标记Cache池中的每个Cache块忙闲状态的数组
        bool isStarted_; //表示Cache池是否启动
        Queue<size_t> queue_; //生产者消费者模型中的队列，在这里表示哪些Cache块可用
        Mutex mutex_; 
        Cond empty_;
        Cond full_;
        ThreadTimer timer_; //定时器用来定时刷新所有Cache块，并保存最新Cache内容到磁盘
};

#endif  /*CACHEMANAGER_H*/
