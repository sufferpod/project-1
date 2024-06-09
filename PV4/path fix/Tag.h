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
    Node<Tag> *temp = Gtags.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        if (temp->data->veiwTitle() == ti)
            return NULL;
        temp = temp->next;
    }
    Tag *tempT = new Tag(ti);
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
    Node<Tag> *temp = Gtags.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        cout << "ID: " << i << endl;
        temp->data->print();
        temp = temp->next;
    }
    cout << endl;
}