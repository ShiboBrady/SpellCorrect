#include "Mutex.h"
#include <stdexcept>
#include <assert.h>

using namespace std;

Mutex::Mutex()
    :isLocked_(false)
{
    if(pthread_mutex_init(&mutex_, NULL))
        throw runtime_error("init mutex");
}

Mutex::~Mutex()
{
    assert(!isMutexLock());
    if(pthread_mutex_destroy(&mutex_))
        throw runtime_error("destroy mutex");
}

void Mutex::lock()
{
    if(pthread_mutex_lock(&mutex_))
        throw runtime_error("lock mutex");
    isLocked_ = true;
}

void Mutex::unlock()
{
    if(pthread_mutex_unlock(&mutex_))
        throw runtime_error("unlock mutex");
    isLocked_ = false;
}

MutexGuade::MutexGuade(Mutex &mutex)
    :mutex_(mutex)
{
    mutex_.lock();
}

MutexGuade::~MutexGuade()
{
    mutex_.unlock();
}
