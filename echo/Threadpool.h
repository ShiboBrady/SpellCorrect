#ifndef THREADPOOL_H
#define THREADPOOL_H 

#include "Queue.hpp"
#include "Mutex.h"
#include "Cond.h"
#include "NonCopyable.h"
#include "Thread.h"
#include <functional>
#include <memory>
#include <vector>

class Threadpool : NonCopyable
{
    public:
        typedef std::function<void ()> Task;
        Threadpool(size_t poolSize, size_t queueSize);
        ~Threadpool();
        void start();
        void threadfunc();
        void add_task(const Task &task);
        Task get_task();
        void stop();
    private:
        size_t pollSize_;
        size_t queueSize_;
        Queue<Task> queue_;
        Mutex mutex_;
        Cond full_;
        Cond empty_;
        bool isStart_;
        std::vector<std::unique_ptr<Thread> > thread_;
};

#endif  /*THREADPOOL_H*/
