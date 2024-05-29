#include <iostream>
#include "question.h"
#include "structs.h"
using namespace std;

class FourChoice : public Question
{
public:
    FourChoice(string Qu, DateTime ti, string A, string B, string C, string D, char answer) : Question(Qu, "FourChoice", ti), A(A), B(B), C(C), D(D), answer(answer) {}
    void print()
    {

        cout << "A) " << A << endl
             << "B) " << B << endl
             << "C) " << C << endl
             << "D) " << D << endl;
    }
    static FourChoice *create(string question, DataTime creatAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};
FourChoice *FourChoice::static create(string question, DataTime creatAt, User user, string A, string B, string C, string D, char answer)
{
}