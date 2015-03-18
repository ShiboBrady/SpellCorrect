#ifndef LOG_H
#define LOG_H 
#include "Queue.hpp"
#include "Tools.h"
#include "Mutex.h"
#include "Cond.h"
#include "Thread.h"

class Log
{
    public:
        Log(const std::string &logfile);
        void stop();
        void addLog(const std::string &str);
        void getLog();
        void writeLog(const std::string &str);
    private:
        std::string logfile_;
        bool isStarted_;
        Queue<std::string> queue_;
        Mutex mutex_;
        Cond cond_;
        Thread thread_;//负责获取日志信息并写入文件的线程
};

#endif  /*LOG_H*/
