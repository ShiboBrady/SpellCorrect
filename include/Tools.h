#ifndef TOOLS_H
#define TOOLS_H 

#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define N 20

namespace tools
{
    //计算最短编辑距离的函数
    int getUFT8Len(char c);
    void makeUFT8ToUint32(const std::string &s, std::vector<uint32_t> &vec);
    inline int min(int a, int b, int c);
    int med_(const std::vector<uint32_t> &x, const std::vector<uint32_t> &y);
    int calcMed(const std::string &s1, const std::string &s2);
    
    //以读写方式打开文件的函数
    std::ifstream &openfileRead(std::ifstream &os, const std::string &filename);
    std::ofstream &openfileWrite(std::ofstream &os, const std::string &filename);

    //去掉字符串最后面的换行符的函数
    void trimSpace(std::string &word);
}


#endif  /*TOOLS_H*/
