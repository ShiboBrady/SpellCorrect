#ifndef MAKEDICTCH_H
#define MAKEDICTCH_H 
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "MixSegment.hpp"

class MakeDictCh
{
    public:
        MakeDictCh(const char *dict_path, const char *model_path);
        void readfile(const std::string &filename, const std::string &exclidefile);
        void writefile(const std::string &filename);
    private:
        std::ifstream &openFileRead(std::ifstream &os, const std::string &filename);
        std::ofstream &openFileWrite(std::ofstream &os, const std::string &filename);
        CppJieba::MixSegment segment_;
        std::map<std::string, int> frequence_;
        std::set<std::string> exclude_;
};

#endif  /*MAKEDICTCH_H*/
