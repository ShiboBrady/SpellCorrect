#ifndef TIMER_H
#define TIMER_H 

#include <functional>
#include <sys/timerfd.h>

class Timer
{
    public:
        typedef std::function<void()> TimerCallbackFuncp;
        Timer();
        ~Timer();

        void setTimer(int val, int interval);
        void setFunction(TimerCallbackFuncp func){func_ = func;}
        void runTimer();
        void stopTimer();
    private:
        int timerfd_;
        struct itimerspec howlong_;
        bool isStarted_;
        TimerCallbackFuncp func_;
};

#endif  /*TIMER_H*/
