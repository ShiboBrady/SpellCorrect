#include "GetConfig.h"
#include "Tools.h"
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace tools;

GetConfig *GetConfig::pInstance_ = NULL;
pthread_once_t GetConfig::once_ = PTHREAD_ONCE_INIT;

void GetConfig::readConf(const string &filename)
{
    ifstream in;
    if(!openfileRead(in, filename))
        throw runtime_error("open config file fail.");
    string line;
    while(getline(in, line)){
        string type;
        string param;
        string::size_type pos;
        pos = line.find("=");
        type = line.substr(0, pos);
        param = line.substr(pos + 1);
        //cout << "type: " << type << " param: " << param << endl;

        if(type == "port")
            port_ = atoi(param.c_str());
        else if(type == "log")
            logfile_ = param;
        else if(type == "cache")
            cachefile_ = param;
        else if(type == "enStorage")
            enstoragefile_ = param;
        else if(type == "chStorage")
            chstoragefile_ = param;
        else if(type == "cachenum")
            cachenum_ = atoi(param.c_str());
        else if(type == "updatefrequence")
            updatefrequence_ = atoi(param.c_str());
    }
}
