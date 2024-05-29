#include <iostream>
#include "question.h"
#include "structs.h"
using namespace std;

class FourChoice : public Question
{
public:
    void printAll();
    FourChoice(string Qu, DateTime ti, User us, string A, string B, string C, string D, char answer) : Question(Qu, "FourChoice", ti, us), A(A), B(B), C(C), D(D), answer(answer) {}
    void print()
    {

        cout << "A) " << A << endl
             << "B) " << B << endl
             << "C) " << C << endl
             << "D) " << D << endl;
    }
     FourChoice  *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);
    static FourChoice  *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

 FourChoice *FourChoice::edit(string question, DateTime createdAt , User user, string A, string B, string C, string D, char answer)
{
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
    this->answer = answer;
    return new FourChoice(question, createdAt, user, A, B, C, D, answer);
    
}
static FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    FourChoice x(question, createdAt, user, A, B, C, D, answer);
    return &x;
}