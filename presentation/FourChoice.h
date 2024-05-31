#pragma once
#include <iostream>
#include "question.h"
#include "permission.h"
#include "Auth.h"

using namespace std;

class FourChoice : public Question
{
public:
    FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans);
    void print();
    void printAll();
    Question *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) override;
    Question *edit(string, DateTime, User);
    static FourChoice *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

FourChoice::FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans) : Question(Qu, "four-choice", ti, us), A(a), B(b), C(c), D(d), answer(ans) {}

void FourChoice::print()
{
    cout << "Question: " << question << endl
         << "A) " << A << endl
         << "B) " << B << endl
         << "C) " << C << endl
         << "D) " << D << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: ";
    user.print();
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    if (isPublished)
        cout << "\nThis question is published\n";
    else
        cout << "This question is not published\n";
}

void FourChoice::printAll()
{
    for (int i = 0; questions[i] != NULL; i++)
    {
        if (questions[i]->TypeBack() == "four-choice")
        {
            cout << "ID : " << i << endl;
            questions[i]->print();
        }
    }
}

Question *FourChoice::edit(string, DateTime, User) { return NULL; }
Question *FourChoice::edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("edit-four-choice-question"))
    {
        this->question = question;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->answer = answer;
        return new FourChoice(question, createdAt, user, A, B, C, D, answer);
    }
    else
        return NULL;
}

FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("add-four-choice-question"))
    {
        FourChoice *x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        int i = 0;
        for (; questions[i] != NULL; i++)
        {
            ;
        }
        questions[i] = x;
        x->publish();
        return x;
    }
    return NULL;
}
