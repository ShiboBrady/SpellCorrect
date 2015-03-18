#include "Log.h"

int main(int argc, const char *argv[])
{
    Log my_log("log.txt");
    my_log.addLog("Hello");
    my_log.addLog("World");
    my_log.addLog("zhangshibo");
    sleep(5);
    my_log.stop();
    return 0;
}
