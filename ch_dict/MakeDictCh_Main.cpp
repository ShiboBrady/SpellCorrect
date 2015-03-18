#include "MakeDictCh.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    const char * const dict_path =  "../dict/jieba.dict.utf8";
    const char * const model_path = "../dict/hmm_model.utf8";
    string readfilename = "../data/ch_in.txt";
    string readExcludeFile = "../data/ch_exclude.txt";
    string writefilename = "../data/ch_out.txt";
    MakeDictCh makedict(dict_path, model_path);
    makedict.readfile(readfilename, readExcludeFile);
    makedict.writefile(writefilename);
    return 0;
}
