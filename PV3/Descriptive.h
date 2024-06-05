#pragma once
#include <iostream>
#include "Question.h"
#include "Permission.h"
#include "Auth.h"

using namespace std;

class Descriptive : public Question
{
    friend void unLoadQuestions();

public:
    Descriptive(string qu, DateTime cr, User us);
    void AddAnswer(string ans);
    void print();
    void printAll();
    static Descriptive *create(string question, DateTime createdAt, User user);
    Question *edit(string, DateTime, User, string, string, string, string, char);
    Question *edit(string question, DateTime createdAt, User user) override;

private:
    string answer;
};

Descriptive::Descriptive(string qu, DateTime cr, User us) : Question(qu, "descriptive", cr, us) {}

void Descriptive::AddAnswer(string ans)
{
    answer = ans;
}

void Descriptive::print()
{
    cout << "Question: " << question << endl
         << "Answer: " << answer << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: \n";
    user.print();
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
    if (isPublished)
        cout << "This question is published\n";
    else
        cout << "This question is not published\n";
}

void Descriptive::printAll()
{
    for (int i = 0; Gquestions.give(i) != NULL; i++)
    {
        if (Gquestions.give(i)->TypeBack() == "descriptive")
        {
            cout << "ID : " << i << endl;
            Gquestions.give(i)->print();
        }
    }
}

Descriptive *Descriptive::create(string question, DateTime createdAt, User user)
{
    if (Auth::whoami()->checkPermTi("add-descriptive-question"))
    {
        Descriptive *x = new Descriptive(question, createdAt, user);
        Gquestions.append(x);
        x->publish();
        return x;
    }
    else
    {
        cout << "You don't have the \"add-descriptive-question\" permission\n";
        return NULL;
    }
    return NULL;
}

Question *Descriptive::edit(string, DateTime, User, string, string, string, string, char) { return NULL; }
Question *Descriptive::edit(string question, DateTime createdAt, User user)
{
    if (Auth::whoami()->checkPermTi("edit-descriptive-question"))
    {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        return new Descriptive(question, createdAt, user);
    }
    else
    {
        cout << "You don't have the \"edit-descriptive-question\" permission\n";
        return NULL;
    }
    return NULL;
}
