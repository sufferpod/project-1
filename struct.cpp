#include <iostream>
using namespace std;

class FourChoice
{
public:
    FourChoice(string A, string B, string C, string D, char answer) : A(A), B(B), C(C), D(D), answer(answer) {}

private:
    string A, B, C, D;
    char answer;
};
