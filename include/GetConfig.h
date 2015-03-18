#ifndef GETCONFIG_H
#define GETCONFIG_H 

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string>

class GetConfig
{
    public:
        static GetConfig *getInstance()
        {
            pthread_once(&once_, &initInstance);
            return pInstance_;
        }

        static void initInstance()
        {
            ::atexit(&destroyInstance);
            pInstance_ = new GetConfig;
        }
          
        static void destroyInstance()
        {
            std::cout << "destroy" << std::endl;
            delete pInstance_;
        }

        void readConf(const std::string &filename);

        const int getPort() const { return port_; }
        const std::string &getLogFile() const { return logfile_; }
        const std::string &getCacheFile() const { return cachefile_; }
        const std::string &getEnStorageFile() const { return enstoragefile_; }
        const std::string &getChStorageFile() const { return chstoragefile_; }
        const int getCacheNum() const { return cachenum_; }
        const int getUpdateFrequence() const { return updatefrequence_; }

    private:
        GetConfig(){};
        GetConfig(const GetConfig &);
        void operator=(const GetConfig &);

        static GetConfig *pInstance_;
        static pthread_once_t once_;

        int port_;
        std::string logfile_;
        std::string cachefile_;
        std::string enstoragefile_;
        std::string chstoragefile_;
        int cachenum_;
        int updatefrequence_;
};

#endif  /*GETCONFIG_H*/
