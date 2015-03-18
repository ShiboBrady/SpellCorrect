#ifndef CACHE_H
#define CACHE_H 

#include "Mutex.h"
#include <map>
#include <list>
#include <string>

class Cache
{
    public:
        Cache(size_t size = 10); 
        std::map<std::string, std::string> &getCache()
        { return cache_; }
        void readCacheFile(const std::string &filename);
        void writeCacheFile(const std::string &filename);
        const std::string getFromCache(const std::string &usrword);
        void putInCache(const std::string &usrword, const std::string &libword);
        void setOrder(size_t order){ order_ = order; }
        size_t getOrder() { return order_; };
        void printCache();
    private:
        size_t order_; //用来标记CacheManager类中此Cache在Cache池中的序号
        std::map<std::string, std::string> cache_; //Cache的数据结构
        std::list<std::string> lru_; //最近最少使用算法使用的数据结构
        size_t size_;//Cache存放数据的最大上限
};

#endif  /*CACHE_H*/
