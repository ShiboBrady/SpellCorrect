#ifndef MAKEDICTEN_h
#define MAKEDICTEN_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

class MakeDictEn
{
    public:
        void readfile(const std::string &filename);
        void writefile(const std::string &filename);
    private:
        std::ifstream &openfileRead(std::ifstream &os, const std::string &filename);
        std::ofstream &openfileWrite(std::ofstream &os, const std::string &filename);
        std::vector<std::string> lines_;
        std::map<std::string, size_t>words_; 
};

#endif  /*MAKEDICTEN_H*/
