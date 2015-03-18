#include "Tools.h"
#include "TextQuery.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace tools;

int main(int argc, const char *argv[])
{
    TextQuery search("../data/en_out.txt", "../data/ch_out.txt");
    string word;
    while(cin >> word)
        cout << search.query(word) << endl;
    return 0;
}
