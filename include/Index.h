#ifndef INDEX_H
#define INDEX_H 

#include "Word.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

class Index
{
    public:
        Index():index_(26){}
        //创建一个索引表，支持英文和中文
        void createIndex(const std::unordered_map<std::string, Word> &dict);
        //返回要查询单词所在的范围
        void createUnionSet(const std::string &usrWord, std::set<Word> &union_set);
    private:
        std::unordered_map<uint32_t, std::set<Word> > index_; //Index的数据结构
};

#endif  /*INDEX_H*/
