#include "Permission.h"

using namespace std;

int main()
{
    Gpermissions.append(new Permission(basicperm[0]));
    Gpermissions.give(0)->print();
    return 0;
}