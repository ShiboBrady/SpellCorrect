#include "MakeDictEn.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    MakeDictEn count;
    string infile;
    cout << "Input a filename to read:" << endl;
    cin >> infile;
    count.readfile(infile);
    string outfile;
    cout << "Input a filename to write:" << endl;
    cin >> outfile;
    count.writefile(outfile);
    return 0;
}
