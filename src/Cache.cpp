#include "Cache.h"
#include "Tools.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace tools;

Cache::Cache(size_t size)
    :size_(size)
{
}

void Cache::readCacheFile(const string &filename)
{
     ifstream in;
     if(!openfileRead(in, filename))
         throw runtime_error("open cache file to read failed");
     string line;
     string usrword;
     string libword;
     //以行为单位将Cache资料读入内存
     while(getline(in, line)){
        istringstream iss(line);
        iss >> usrword >> libword;
        cache_.insert(make_pair(usrword, libword));
        //lru_.pushback(usrword);
     }
     in.close();
     in.clear();
}

void Cache::writeCacheFile(const string &filename)
{
    ofstream out;
    if(!openfileWrite(out, filename))
        throw runtime_error("open cache file to write failed.");
    map<string, string>::iterator it;
    for(it = cache_.begin(); it != cache_.end(); ++it)
        out << it->first << " " << it->second << endl;
    out.close();
    out.clear();
}

const string Cache::getFromCache(const string &usrword)
{
    map<string, string>::iterator mapit;
    list<string>::iterator listit;
    string rtn("");
    //在Cache中查找
    mapit = cache_.find(usrword);
    if(mapit != cache_.end()){
        rtn = mapit->second;
        listit = find(lru_.begin(), lru_.end(), usrword);
        assert(listit != lru_.end());
        //将list中的单词换到链表开头位置，表示刚访问过。
        lru_.erase(listit);
        lru_.push_front(usrword);
    }
    return rtn;
}

void Cache::putInCache(const string &usrword, const string &libword)
{
    cache_.insert(make_pair(usrword, libword));
    //如果此时Cache以达到最大上限，就要将最后的一项移除
    if(lru_.size() >= size_)
        getFromCache(lru_.back());    
    //将新建项插入list的最开始位置
    lru_.push_front(usrword);
}

void Cache::printCache()
{
    map<string, string>::iterator it;
    for(it = cache_.begin(); it != cache_.end(); ++it){
        cout << "Usrword: " << it->first << " Match: " << it->second << endl;
    }
}
