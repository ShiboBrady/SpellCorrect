#include "Tools.h"
#include<iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace tools;
using namespace std;

int main(int argc, const char *argv[])
{
    string s("你好吗");
    string s1("你好");
    vector<uint32_t> vec;
    makeUFT8ToUint32(s, vec);
    for(vector<uint32_t>::iterator it = vec.begin(); it != vec.end(); ++it){
        //cout << *it << endl;    
        printf("%x\n", *it);
    }
    vec.clear();
    makeUFT8ToUint32(s1, vec);
    for(vector<uint32_t>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }

    cout << calcMed(s, s1) << endl;
    return 0;
}
