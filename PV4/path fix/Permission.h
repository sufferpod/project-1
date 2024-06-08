#pragma once
#include <iostream>
#include "LinkList.h"
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
    Node<Permission> *temp = Gpermissions.returnHead();
    while (temp != NULL)
    {
        if (temp->data->title == x->title)
            return NULL;
        temp = temp->next;
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