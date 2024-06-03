#pragma once
#include <iostream>
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

#include "Database.h"

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    int i = 0;
    for (; Gpermissions[i] != NULL; i++)
    {
        if (Gpermissions[i]->title == x->title)
        {
            break;
        }
    }
    if (Gpermissions[i] == NULL)
    {
        Gpermissions[i] = x;
    }
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
