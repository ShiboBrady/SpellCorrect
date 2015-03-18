#include "MakeDictCh.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

MakeDictCh::MakeDictCh(const char *dect_path, const char *model_path)
    :segment_(dect_path, model_path)
{
     
}

void MakeDictCh::readfile(const string &filename, const string &excludefile)
{
    ifstream in;
    if(!openFileRead(in, excludefile))
        throw runtime_error("open exclude file to read fail.");
    string charactor;
    while(in >> charactor){
        exclude_.insert(charactor);
    }

    if(!openFileRead(in, filename))
        throw runtime_error("open chinese atricle to read fail.");
    string line;
    for(size_t i = 0; i < line.size(); ++i){
        if(line[i] <= 127)
            line[i] = 32;
    }
    while(getline(in, line)){
        vector<string> words;
        segment_.cut(line, words);
        set<string>::iterator setit;
        for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
            setit = exclude_.find(*it);
            if(setit == exclude_.end())
                frequence_[(*it)]++;
        }
    }
}

void MakeDictCh::writefile(const string &filename)
{
    ofstream out;
    if(!openFileWrite(out, filename))
        throw runtime_error("open chinese article to write fail.");
    map<string, int>::iterator it;
    for(it = frequence_.begin(); it != frequence_.end(); ++it)
        out << it->first << " " << it->second << endl;
}

ifstream &MakeDictCh::openFileRead(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}

ofstream &MakeDictCh::openFileWrite(ofstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
