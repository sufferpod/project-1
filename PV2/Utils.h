#pragma once
#include <cstdlib>

void clear()
{
#ifdef __linux__
    system("clear");
#elif _WIN64
    system("cls");
#endif
}