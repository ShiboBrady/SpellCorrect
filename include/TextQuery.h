#ifndef SEARCH_H
#define SEARCH_H 
#include "Word.h"
#include "Cache.h"
#include "Index.h"
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>

class TextQuery
{
    public:
        TextQuery(const std::string &enStorageFile, const std::string &chStorageFile);
        std::string query(const std::string &str);
    private:
        void readFile(int flag);

        std::unordered_map<std::string, Word> storage_;  //词库
        const std::string enStorageFile_; //英语词库文件
        const std::string chStorageFile_;//汉语词库文件
        Index index_;
};

#endif  /*SEARCH_H*/
