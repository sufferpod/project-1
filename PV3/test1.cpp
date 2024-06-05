#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream openedFile("/home/suffer/project 1/PV3/DataBase.txt", ios::in);
    string a[3];

    openedFile.close();
    return 0;
}