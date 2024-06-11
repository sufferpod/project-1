#pragma once
#include <string>
#include "Structs.h"
#include "LinkedList.h"
#include "Users.h"
#include "Tag.h"
using namespace std;

class Question
{
    friend void unLoadQuestions();

public:
    Question(string Qu, string ty, DateTime ti, User us) : question(Qu), type(ty), createdAt(ti), user(us) {}
    void publish() { isPublished = true; }
    void unpublish() { isPublished = false; }
    virtual void print() = 0;
    virtual void printAll() = 0;
    virtual Question *edit(string, DateTime, User, string, string, string, string, char) = 0;
    virtual Question *edit(string, DateTime, User) = 0;
    virtual void addAnswer(string) = 0;
    void addTag(Tag *);
    bool pubBack();
    string TypeBack();

protected:
    string question;
    string type;
    DateTime createdAt;
    User user;
    Tag *tags[100] = {NULL};
    bool isPublished = false;
};

void Question::addTag(Tag *tag)
{
    int i = 0;
    for (; tags[i] != NULL; i++)
    {
        if (tags[i] == tag)
            return;
    }
    tags[i] = tag;
}

bool Question::pubBack()
{
    return isPublished;
}

string Question::TypeBack()
{
    return type;
}

linkedList<Question> Gquestions;