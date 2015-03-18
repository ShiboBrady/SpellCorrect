#include "Log.h"
#include <functional>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

Log::Log(const string &logfile)
    :logfile_(logfile),
     isStarted_(false),
     cond_(mutex_),
     thread_(bind(&Log::getLog, this))
{    
    thread_.start();
    isStarted_ = true;
}

void Log::stop()
{
    isStarted_ = false;
    cond_.broadcast();
    thread_.stop();
}

void Log::addLog(const string &str)
{
    mutex_.lock();
    queue_.enqueue(str);
    //如果此数据是向空队列中放入的第一个数据块，就给等待线程发出通知信号
    if(queue_.getSize() == 1)
        cond_.signal();
    mutex_.unlock();
}

void Log::getLog()
{
    //终止的条件是Log类已停止
    while(isStarted_){
        mutex_.lock();
        //如果队列为空，就释放锁，并等待信号
        while(isStarted_ && queue_.isEmpty())
            cond_.wait();
        string str;
        if(!queue_.isEmpty()){
            queue_.dequeue(str);
            writeLog(str); 
        }else{
            writeLog("Server is stop.");
        }
        mutex_.unlock();
    }
}

void Log::writeLog(const string &str)
{
    ofstream out;
    out.open(logfile_, ofstream::app);
    if(!out)
        throw runtime_error("log file can't open");
    out << str << endl;
    out.close();
    out.clear();
}
