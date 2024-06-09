#pragma once
#include <iostream>
#include "LinkedList.h"

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
    Tag *temp = new Tag(ti);
    int i = 0;
    for (; Gtags.give(i) != NULL; i++)
    {
        if (Gtags.give(i)->veiwTitle() == ti)
            break;
    }
    if (Gtags.give(i) == NULL)
    {
        Gtags.append(temp);
        return temp;
    }
    return NULL;
}

string Tag::veiwTitle()
{
    return title;
}

void Tag::print()
{
    cout << title;
}

void Tag::printAll()
{
    cout << "tags: \n";
    for (int i = 0; Gtags.give(i) != NULL; i++)
    {
        cout << "ID: " << i << '=';
        Gtags.give(i)->print();
        cout << endl;
    }
    cout << endl;
}
