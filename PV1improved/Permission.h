#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

class Permission
{
private:
    string title;

public:
    Permission(string per) : title(per) {}
    static Permission *create(string ti);
    void print();
    string viewTitle();
};

string basicperm[5]{
    "add-descriptive-question", "add-four-choice-question",
    "edit-descriptive-question", "edit-four-choice-question",
    "add-user"};

Permission *Gpermissions[100] = {NULL};

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    int i = 0;
    for (; Gpermissions[i] != NULL; i++)
    {
        if (Gpermissions[i]->title == x->title)
            return NULL;
    }
    Gpermissions[i] = x;
    return x;
}

void Permission::print()
{
    cout << title << endl;
}

string Permission::viewTitle()
{
    return title;
}