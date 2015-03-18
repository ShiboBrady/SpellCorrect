#include "Tools.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace tools;

int main(int argc, const char *argv[])
{
    string s = "天龙八部很好看";
    cout << tools::getUFT8Len(s[0]) << endl;
    string s1 = "八";
    cout << calcMed(s, s1) << endl;
    return 0;
}
