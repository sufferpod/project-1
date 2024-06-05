#include <fstream>
using namespace std;

int main()
{
    fstream openedFile("DataBase.txt");
    openedFile << "kiki" << endl;
    openedFile.close();
    return 0;
}