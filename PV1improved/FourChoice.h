#pragma once
#include <iostream>
#include "Question.h"
#include "Permission.h"
#include "Auth.h"

using namespace std;

class FourChoice : public Question
{
    friend void unLoadQuestions();

public:
    FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans) : Question(Qu, "four-choice", ti, us), A(a), B(b), C(c), D(d), answer(ans) {}
    void print();
    void printAll();
    Question *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) override;
    Question *edit(string, DateTime, User);
    void addAnswer(string) {}
    static FourChoice *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("add-four-choice-question"))
    {
        FourChoice *x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        int i = 0;
        for (; Gquestions[i] != NULL; i++)
        {
            ;
        }
        x->publish();
        Gquestions[i] = x;
        return x;
    }
    else
    {
        cout << "You don't have the \"add-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
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
        this->createdAt = createdAt;
        this->user = user;
        return this;
    }
    else
    {
        cout << "You don't have the \"edit-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
}

void FourChoice::print()
{
    cout << "Question: " << question << endl
         << "A) " << A << endl
         << "B) " << B << endl
         << "C) " << C << endl
         << "D) " << D << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: " << user.myName() << endl;
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
}

void FourChoice::printAll()
{
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        if (Gquestions[i]->TypeBack() == "four-choice")
        {
            if (Gquestions[i]->pubBack())
            {
                cout << "ID : " << i << endl;
                Gquestions[i]->print();
            }
            else
                cout << "ID: " << i << " Not published\n";
        }
    }
}