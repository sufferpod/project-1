#pragma once
#include <iostream>

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

Tag *Gtags[100] = {NULL};

Tag *Tag::create(string ti)
{
    Tag *temp = new Tag(ti);
    int i = 0;
    for (; Gtags[i] != NULL; i++)
    {
        if (Gtags[i]->veiwTitle() == ti)
            return NULL;
    }
    Gtags[i] = temp;
    return temp;
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
    for (int i = 0; Gtags[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        Gtags[i]->print();
    }
    cout << endl;
}