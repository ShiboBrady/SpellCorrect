#include "Index.h"
#include "Tools.h"

using namespace std;
using namespace tools;

void Index::createIndex(const std::unordered_map<string, Word> &storage)
{
    unordered_map<string, Word>::const_iterator mapit;
    //将词库中的每个单词都读入索引表中
    for(mapit = storage.begin(); mapit != storage.end(); ++mapit){
        //将一个单词转换成uint32_t类型的数组
        string word = mapit->first;
        vector<uint32_t> uvec;
        tools::makeUFT8ToUint32(word, uvec);
        //将单词放在以uint32_t数组每个元素为索引项的项目里
        for(vector<uint32_t>::size_type i = 0; i != uvec.size(); ++ i){
            index_[uvec[i]].insert(mapit->second); 
        }         
    }
}

void Index::createUnionSet(const string &usrWord, set<Word> &union_set)
{
    //将一个单词转换成uint32_t类型的数组
    string word = usrWord;
    vector<uint32_t> uvec;
    tools::makeUFT8ToUint32(word, uvec);
    set<Word>::iterator begin;
    set<Word>::iterator end;
    //将以uint32_t数组中的每个元素为索引的项目合并为一个并集
    for(vector<uint32_t>::size_type i = 0; i < uvec.size(); ++i){
        begin = index_[uvec[i] ].begin();
        end = index_[uvec[i] ].end();
        union_set.insert(begin, end);
    }
}

