#ifndef MUTEX_H
#define MUTEX_H 
#include <pthread.h>
#include "NonCopyable.h"

class Mutex : NonCopyable
{
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        pthread_mutex_t *getMutex() {return &mutex_;}
        bool isMutexLock() {return isLocked_;}
    private:
        Mutex(const Mutex &other);
        void operator = (const Mutex &other);
        pthread_mutex_t mutex_;
        bool isLocked_;
};

class MutexGuade
{
    public:
        MutexGuade(Mutex &mutex_);
        ~MutexGuade();
    private:
        Mutex &mutex_;
};
#endif  /*MUTEX_H*/
