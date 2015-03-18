#include "Threadpool.h"
#include <iostream>
#define MutexGuide(mutex_) "ERROR"
using namespace std;

Threadpool::Threadpool(size_t pollSize, size_t queueSize)
    :pollSize_(pollSize),
     queueSize_(queueSize),
     queue_(),
     mutex_(),
     full_(mutex_),
     empty_(mutex_),
     isStart_(false)
{
}

Threadpool::~Threadpool()
{
    if(isStart_)
        stop();
}

void Threadpool::threadfunc()
{
    Task task;
    while(isStart_){
        task = get_task();
        if(task){
            task();
        }
    }
}

void Threadpool::start()
{
    if(!isStart_){
        isStart_ = true;
        for(size_t i = 0; i < pollSize_; ++i)
            thread_.push_back(std::unique_ptr<Thread>(new Thread(bind(&Threadpool::threadfunc, this))));
        for(size_t i= 0; i < pollSize_; ++i)
            thread_[i]->start();
    } 
}

void Threadpool::add_task(const Task &task)
{
    MutexGuade lock(mutex_);
    while(queue_.getSize() >= queueSize_)
        empty_.wait();
    queue_.enqueue(task);
    if(queue_.getSize() == 1)
        full_.signal();
}

Threadpool::Task Threadpool::get_task()
{
    MutexGuade lock(mutex_);
    while(isStart_ && queue_.isEmpty())
        full_.wait();
    Task task = NULL;
    if(!queue_.isEmpty()){
        queue_.dequeue(task);
        if(queue_.getSize() == (queueSize_ - 1))
            empty_.signal();
    }
    return task;
}

void Threadpool::stop()
{
    if(isStart_){
        {
            MutexGuade lock(mutex_);
            isStart_ = false;
            full_.broadcast();
        }
        for(size_t i = 0; i < pollSize_; ++i)
            thread_[i]->stop();
    } 
    queue_.clear();
    thread_.clear();
    cout << "All thread is stop." << endl;
}
