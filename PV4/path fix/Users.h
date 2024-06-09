#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Permission.h"
using namespace std;

class User
{
    friend void unLoadUsers();
    friend void unLoadQuestions();

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

linkedList<User> Gusers;

User *User::create(string n, string un, string pa, User *ami)
{
    if (ami->checkPermTi("add-user"))
    {
        if (!ami->checkAuth(un, pa))
        {
            User *x = new User(n, un, pa);
            Gusers.append(x);
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
        if (permissions[i] == permission)
            return;
    }
    permissions[i] = permission;
}

void User::print()
{
    cout << "Name: " << name
         << "\nUser name: " << username
         << "\nPassword: " << password
         << "\nPermissions: \n";
    for (int i = 0; permissions[i] != NULL; i++)
        permissions[i]->print();
}

void User::printAll()
{
    Node<User> *temp = Gusers.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        cout << "ID: " << i << endl;
        temp->data->print();
        temp = temp->next;
    }
}

bool User::checkAuth(string un, string pa)
{
    if (username == un && password == pa)
        return true;
    return false;
}

bool User::checkPermTi(string ti)
{
    for (int i = 0; permissions[i] != NULL; i++)
    {
        if (permissions[i]->viewTitle() == ti)
            return true;
    }
    return false;
}

string User::myName()
{
    return username;
}