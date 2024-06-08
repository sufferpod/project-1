#pragma once
#include <iostream>
#include "LinkList.h"

using namespace std;

class Tag
{
private:
    string title;

public:
    Tag(string ti) : title(ti) {}
    static Tag *create(string ti);
    string veiwTitle();
    void print();
    static void printAll();
};

linkedList<Tag> Gtags;

Tag *Tag::create(string ti)
{
    Tag *tempT = new Tag(ti);
    Tag *temp = Gtags.give(0);
    for (int i = 1; temp != NULL; i++)
    {
        if (temp->veiwTitle() == ti)
            return NULL;
        temp = Gtags.give(i);
    }
    Gtags.append(tempT);
    return tempT;
}

string Tag::veiwTitle()
{
    return title;
}

void Tag::print()
{
    cout << title << endl;
}

void Tag::printAll()
{
    cout << "tags: \n";
    Tag *temp = Gtags.give(0);
    for (int i = 1; temp != NULL; i++)
    {
        cout << "ID: " << i - 1 << '=';
        temp->print();
        temp = Gtags.give(i);
    }
    cout << endl;
}
