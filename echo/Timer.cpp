#include "Timer.h"
#include <poll.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

using namespace std;

Timer::Timer()
    :isStarted_(false)
{
    if(-1 == (timerfd_ = timerfd_create(CLOCK_REALTIME, 0)))
        ERR_EXIT("timerfd_create");
}

Timer::~Timer()
{
    close(timerfd_);
}

void Timer::setTimer(int val, int interval)
{
    bzero(&howlong_, sizeof(howlong_));
    howlong_.it_value.tv_sec = val;
    howlong_.it_interval.tv_sec = interval;
}

void Timer::runTimer()
{
    struct pollfd event[1];
    event[0].fd = timerfd_;
    event[0].events = POLLIN;
    int ret;
    int nready;
    char buf[1024] = {0};

    if(-1 == timerfd_settime(timerfd_, 0, &howlong_, NULL))
        ERR_EXIT("timerfd_settime");

    isStarted_ = true;

    while(isStarted_){
        nready = poll(event, 1, 10000);
        if(nready == -1)
            ERR_EXIT("poll");
        else if(nready == 0)
            cout << "Timeout" << endl;
        else{
            ret = read(timerfd_, buf, 1024);
            if(ret == -1){
                if(errno == EINTR)
                    continue;
                ERR_EXIT("read"); 
            }else if(ret == 0)
                continue;
            func_();
        }
    }
}

void Timer::stopTimer()
{
    howlong_.it_value.tv_sec = 0;
    howlong_.it_interval.tv_sec = 0;
    if(-1 == timerfd_settime(timerfd_, 0, &howlong_, NULL))
        ERR_EXIT("timerfd_settime");
    isStarted_ = false;
}
