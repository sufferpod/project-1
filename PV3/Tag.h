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
    int i = 0;
    for (Tag *temp = Gtags.give(i); temp != NULL; i++)
    {
        if (temp->veiwTitle() == ti)
            return NULL;
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
    int i = 0;
    for (Tag *temp = Gtags.give(i); temp != NULL; i++)
    {
        cout << "ID: " << i << '=';
        temp->print();
    }
    cout << endl;
}
