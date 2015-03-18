#include "Cond.h"
#include "Mutex.h"
#include <stdexcept>
#include <assert.h>

using namespace std;

Cond::Cond(Mutex &mutex)
    :mutex_(mutex)
{
    if(pthread_cond_init(&cond_, NULL))
        throw runtime_error("cond init");
}

Cond::~Cond()
{
    if(pthread_cond_destroy(&cond_))
        throw runtime_error("cond destroy");
}

void Cond::wait()
{
    assert(mutex_.isMutexLock());
    if(pthread_cond_wait(&cond_, mutex_.getMutex()))
        throw runtime_error("cond wait");
}

void Cond::signal()
{
    if(pthread_cond_signal(&cond_))
        throw runtime_error("cond signal");
}

void Cond::broadcast()
{
    if(pthread_cond_broadcast(&cond_))
        throw runtime_error("cond broadcast");
}
