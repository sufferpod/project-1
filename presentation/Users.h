#pragma once
#include <iostream>
#include "Permission.h"
using namespace std;

class User
{
private:
    string name, username, password;
    Permission *permissions[100] = {NULL};

public:
    User(string n, string un, string pa) : name(n), username(un), password(pa) {}
    static User *create(string, string, string, User *);
    void addpermission(Permission *permission);
    void print();
    static void printAll();
    bool checkAuth(string, string);
    bool checkPermTi(string);
    string myName();
};
User *users[100] = {NULL};
User *User::create(string n, string un, string pa, User *ami)
{
    User *x = new User(n, un, pa);
    if (ami->checkPermTi("add-user"))
    {
        int i = 0;
        for (; users[i] != NULL; i++)
        {
            ;
        }
        if (!ami->checkAuth(un, pa))
        {
            users[i] = x;
            return x;
        }
    }
    else
    {
        cout << "You don't have the \"add-user\" permission\n";
        return NULL;
    }
    return NULL;
}

void User::addpermission(Permission *permission)
{
    int i = 0;
    for (; permissions[i] != NULL; i++)
    {
        if (permissions[i]->viewTitle() == permission->viewTitle())
        {
            break;
        }
    }

    if (permissions[i] == NULL)
    {
        permissions[i] = permission;
    }
}

void User::print()
{
    cout << "Name: " << name
         << "\nUser name: " << username
         << "\nPassword: " << password << endl;
}

void User::printAll()
{
    for (int i = 0; users[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        users[i]->print();
        cout << endl;
    }
}

bool User::checkAuth(string un, string pa)
{
    if (username == un)
    {
        if (password == pa)
            return true;
    }
    return false;
}

bool User::checkPermTi(string ti)
{
    for (int i = 0; permissions[i] != NULL; i++)
    {
        if (permissions[i]->viewTitle() == ti)
        {
            return true;
        }
    }
    return false;
}

string User::myName()
{
    return username;
}
