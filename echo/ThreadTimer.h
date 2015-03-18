#ifndef THREADTIMER_H
#define THREADTIMER_H 

#include "Thread.h"
#include "Timer.h"
#include <functional>

class ThreadTimer
{
    public:
        typedef std::function<void ()> funcp;
        ThreadTimer()
            :thread_(std::bind(&Timer::runTimer, &timer_)){}
        void setTime(int val, int interval){timer_.setTimer(val, interval); }
        void setFunc(funcp func){timer_.setFunction(func); }
        void start(){thread_.start(); }
        void stop(){timer_.stopTimer(), thread_.stop(); }
    private:
        Thread thread_;
        Timer timer_;
};

#endif  /*THREADTIMER_H*/
