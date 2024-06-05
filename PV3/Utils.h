#pragma once
#include <fstream>
#include "LinkList.h"
#include "Permission.h"
#include "Users.h"
#include "Question.h"
#include <cstdlib>
using namespace std;

void clear()
{
#ifdef __linux__
    system("clear");
#elif _WIN64
    system("cls");
#endif
}

template <class T>
void finalDelete(Node<T> *head)
{
    Node<T> *temp = head;
    while (head != NULL)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

void boot()
{

    for (int i = 0; i < 5; i++)
    {
        Gpermissions.append(new Permission(basicperm[i]));
    }

    Gusers.append(new User("admin", "admin", "123456"));
    for (int i = 0; Gpermissions.give(i) != NULL; i++)
    {
        Gusers.give(0)->addpermission(Gpermissions.give(i));
    }
}

void unboot()
{
    finalDelete<Permission>(Gpermissions.returnHead());
    finalDelete<Tag>(Gtags.returnHead());
    finalDelete<User>(Gusers.returnHead());
    finalDelete<Question>(Gquestions.returnHead());
}