#include "TextQuery.h"
#include "Tools.h"
#include <sstream>
#include <stdexcept>
#include <strings.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;
using namespace tools;

TextQuery::TextQuery(const string &enStorageFile, const string &chStorageFile)
     :enStorageFile_(enStorageFile),
      chStorageFile_(chStorageFile)
{
    readFile(0); //读取英文词库
    readFile(1); //读取汉语词库
    index_.createIndex(storage_);
}

void TextQuery::readFile(int flag)
{
    ifstream in;
    string storageFile = (flag ? chStorageFile_ : enStorageFile_);
    if(!openfileRead(in, storageFile))
        throw runtime_error("open libary file to read fail");
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        string word;
        int fre;
        iss >> word >> fre;
        Word new_word;
        new_word.word_ = word;
        new_word.med_ = 20;
        new_word.frequence_ = fre;
        storage_.insert(make_pair(word, new_word));
    }
    in.close();
    in.clear();
}

string TextQuery::query(const string &word)
{
    //定义一个优先级队列
    priority_queue<Word>queue; 
    //查看是否在词库中，有则直接返回
    //否则就执行匹配运算
    unordered_map<string, Word>::iterator mapit;
    mapit = storage_.find(word);
    if(mapit != storage_.end())
        return word;
    //根据单词取得要查询的范围
    set<Word> union_set;
    index_.createUnionSet(word, union_set);
    set<Word>::iterator it;
    for(it = union_set.begin(); it != union_set.end(); ++it){
        Word new_word = *it;
        new_word.med_ = calcMed(word, it->word_); 
        queue.push(new_word);
    }
    //取出优先级队列中第一个元素， 即最大的那个元素
    string result;
    if(!queue.empty())
        result = queue.top().word_;
    else result = "Try again";
    return result; 
}

