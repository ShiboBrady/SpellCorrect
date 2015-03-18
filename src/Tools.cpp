#include "Tools.h"
#include <string.h>
using namespace std;
using namespace tools;

//打开文件，并返回文件读入流
ifstream &tools::openfileRead(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
//打开文件，并返回文件写入流
ofstream &tools::openfileWrite(ofstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
//计算一个以uft-8编码的字占几个字节
int tools::getUFT8Len(char c)
{
    int cnt = 0;
    while(c & (1 << (7 - cnt))) ++cnt;
    return cnt;
}

//将一个字符转换为四个字节存储
void tools::makeUFT8ToUint32(const std::string &s, std::vector<uint32_t> &vec)
{
    int len;
    for(size_t i = 0; i != s.size(); ++i){
        uint32_t ut = (unsigned char)s[i];
        len = getUFT8Len(s[i]);
        len--;
        if(len > 0){
            while(len--){ 
                ut = (ut << 8) + (unsigned char)s[++i];
            }
        }
        vec.push_back(ut);
    } 
}

//计算三个数的最小值
inline int tools::min(int a, int b, int c)
{
    int ret = a < b ? a : b;
    return (ret < c ? ret : c);
}

//计算两个uint32_t类型数组之间的最小编辑距离
int tools::med_(const std::vector<uint32_t> &x, const std::vector<uint32_t> &y)
{
    int memo_[N][N];
    int m = x.size();
    int n = y.size();
    for(int i = 0; i <= m; ++i)
        memo_[i][0] = i;
    for(int j = 0; j <= n; ++j)
        memo_[0][j] = j;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(x[i-1] == y[j-1])
                memo_[i][j] = memo_[i-1][j-1];
            else{
                int a = memo_[i-1][j];
                int b = memo_[i][j-1];
                int c = memo_[i-1][j-1];
                memo_[i][j] = min(a, b, c) + 1;
            }
        }
    }
   // for(int i = 0; i <= m; ++i){
   //     for(int j = 0; j <= n; ++j)
   //         cout << memo_[i][j] << " ";
   //     cout << endl;
   // }
    return memo_[m][n];
}

//接受两个字符串，将其转换为uint32_t类型的数组，并调用最小编辑距离算法，主要供外界使用
int tools::calcMed(const std::string &s1, const std::string &s2)
{
    std::vector<uint32_t> ut1, ut2;
    makeUFT8ToUint32(s1, ut1);
    makeUFT8ToUint32(s2, ut2);
    return med_(ut1, ut2);
}

//去掉字符串最后面的换行符，用于网络传输
void tools::trimSpace(string &word)
{
    char temp[200] = {0};
    strcpy(temp, word.c_str());
    temp[strlen(temp) - 2] = 0;
    word = string(temp);
}

