#include "MakeDictEn.h"
#include <stdexcept>
#include <sstream>
using namespace std;

void MakeDictEn::readfile(const string &filename)
{
    ifstream in;
    if(!openfileRead(in, filename))
        throw runtime_error("openfile.");
    string line;
    while(getline(in, line)){
        lines_.push_back(line);
        for(size_t i = 0; i < line.size(); ++i){
            if(ispunct(line[i]))
                line[i] = 32;
            if(isupper(line[i]))
                line[i] += 32;
            if(isdigit(line[i]))
                line[i] = 32;
        } 
        istringstream iss(line);
        string word;
        while(iss >> word){
            words_[word]++; 
        }
    }
    in.close();
    in.clear();
}

void MakeDictEn::writefile(const string &filename)
{
    ofstream out;
    if(!openfileWrite(out, filename))
        throw runtime_error("openfile to write.");
    for(map<string, size_t>::iterator it = words_.begin(); it != words_.end(); ++it){
        out << it->first << " " << it->second << endl;
    }
    out.close();
    out.clear();
}

ifstream &MakeDictEn::openfileRead(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}

ofstream &MakeDictEn::openfileWrite(ofstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
