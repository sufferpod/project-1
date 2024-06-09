#pragma once
#include <iostream>
#include "linkedList.h"
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
linkedList<Permission> Gpermissions;

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    int i = 0;
    Permission *temp = Gpermissions.give(0);
    for (int i = 1; temp != NULL; i++)
    {
        if (temp->title == x->title)
            return NULL;
        temp = Gpermissions.give(i);
    }
    Gpermissions.append(x);
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