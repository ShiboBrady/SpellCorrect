#include "Server.h"
#include "GetConfig.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    GetConfig *config = GetConfig::getInstance();
    config->readConf("../conf/config.txt");
    //Server server(config->getPort(), config->getEnStorageFile(), config->getChStorageFile(), config->getCacheFile());
    Server server(config);
    server.start();
    return 0;
}
