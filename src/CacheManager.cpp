#include "CacheManager.h"
#include <iostream>
using namespace std;
CacheManager::CacheManager(const string &cachefile, size_t cacheNum, int updateFrequence)
    :cachefile_(cachefile),
     cacheNum_(cacheNum),
     caches_(cacheNum),
     flags_(cacheNum),
     isStarted_(true),
     empty_(mutex_),
     full_(mutex_)
{
    totalCache_.readCacheFile(cachefile_);
    map<string, string>::iterator beginit = totalCache_.getCache().begin();
    map<string, string>::iterator endit = totalCache_.getCache().end();
    for(vector<Cache>::iterator it = caches_.begin(); it != caches_.end(); ++it)
        it->getCache().insert(beginit, endit);

    for(vector<Cache>::size_type i = 0; i != caches_.size(); ++i){
        caches_[i].setOrder(i);
        flags_[i] = 0;
        queue_.enqueue(i);
    }

    timer_.setTime(10, updateFrequence); 
    timer_.setFunc(::bind(&CacheManager::writeToFile, this));
}

CacheManager::~CacheManager()
{
    timer_.stop();
    stop();
}

void CacheManager::start()
{
    timer_.start();
}
void CacheManager::stop()
{
    if(isStarted_){
        isStarted_ = true;
        full_.broadcast();
    }
}

Cache *CacheManager::getCache()
{
    MutexGuade lock(mutex_);      
    size_t i;
    while(isStarted_ && queue_.isEmpty())
        full_.wait();
    if(!queue_.isEmpty()){
        queue_.dequeue(i);
    }
    //cout << "Cache " << i << " is dequeue." << endl;
    return &caches_[i];
}

void CacheManager::returnCache(size_t i)
{
    MutexGuade lock(mutex_);
    queue_.enqueue(i);
    //cout << "Cache " << i << " is enqueue." << endl;
    //cout << caches_[i].getOrder() << endl;
    //caches_[i].printCache();
    //cout << "enqueue Cache " << i << " size = " << caches_[i].getCache().size() << endl;
    if(queue_.getSize() == 1)
        full_.signal();
}

void CacheManager::writeToFile()
{
    //cout << "timer call." << endl;
    map<string, string>::iterator begin, end;
    for(size_t i = 0; i < cacheNum_; ++i){
        begin = caches_[i].getCache().begin();
        end = caches_[i].getCache().end();
        totalCache_.getCache().insert(begin, end);
    }
    totalCache_.writeCacheFile(cachefile_);
    updateCache();
}

void CacheManager::updateCache()
{
    //cout << "updatecache call." << endl;
    map<string, string>::iterator begin, end;
    begin = totalCache_.getCache().begin();
    end = totalCache_.getCache().end();
    size_t i = 0;
    while(i != cacheNum_){
        Cache *uc = getCache();
        size_t order = uc->getOrder();
        if(flags_[order] == 0){
            uc->getCache().insert(begin, end);
            flags_[order] = 1;
        }
        returnCache(order);
        if(order == i)
            ++i;
    }
    for(vector<size_t>::iterator it = flags_.begin(); it != flags_.end(); ++it){
        *it = 0;
    }
    cout << "update cache once." << endl;
}

