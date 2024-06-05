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

void loadUsers()
{
    fstream Userfile("/home/suffer/project 1/PV3/Users.txt", ios::in);
    string t1, t2, t3;
    while (getline(Userfile, t1))
    {
        getline(Userfile, t2);
        getline(Userfile, t3);
        Gusers.append(new User(t1, t2, t3));
    }
    Userfile.close();
    User *admin = Gusers.give(0);
    for (int i = 0; Gpermissions.give(i) != NULL; i++)
    {
        admin->addpermission(Gpermissions.give(i));
    }
}

void loadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV3/Questions.txt", ios::in);
    string t1, t2, t3;
    while (getline(Qfile, t1))
    {
    }
    Qfile.close();
}

void unLoadUsers()
{
    fstream Userfile("/home/suffer/project 1/PV3/Users.txt", ios::out | ios::trunc);
    for (int i = 0; Gusers.give(i) != NULL; i++)
    {
        User *temp = Gusers.give(i);
        Userfile << temp->name << endl;
        Userfile << temp->username << endl;
        Userfile << temp->password;
        if (temp != Gusers.tail->data)
            Userfile << endl;
    }
    Userfile.close();
}

void unLoadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV3/Questions.txt", ios::out | ios::trunc);
    for (int i = 0; Gquestions.give(i) != NULL; i++)
    {
        Question *temp = Gquestions.give(i);
        if (temp->TypeBack() == "descriptive")
        {
            Qfile << temp->TypeBack() << endl;
            Qfile << temp->question
                  << endl;
            Qfile << temp->createdAt.year << ' ' << temp->createdAt.month << ' '
                  << temp->createdAt.day << ' ' << temp->createdAt.hour << ' '
                  << temp->createdAt.minute << ' ' << temp->createdAt.second
                  << endl;
            Qfile << temp->user.name << endl
                  << temp->user.username << endl
                  << temp->user.password;
            if (temp != Gquestions.tail->data)
                Qfile << endl;
        }
        else
        {
            FourChoice *temp2 = dynamic_cast<FourChoice *>(temp);
            Qfile << temp->TypeBack() << endl;
            Qfile << temp->question
                  << endl;
            Qfile << temp->createdAt.year << ' ' << temp->createdAt.month << ' '
                  << temp->createdAt.day << ' ' << temp->createdAt.hour << ' '
                  << temp->createdAt.minute << ' ' << temp->createdAt.second
                  << endl;
            Qfile << temp->user.name << endl
                  << temp->user.username << endl
                  << temp->user.password << endl;
            Qfile << temp2->A << endl
                  << temp2->B << endl
                  << temp2->C << endl
                  << temp2->D << endl
                  << temp2->answer;
            if (temp != Gquestions.tail->data)
                Qfile << endl;
        }
    }
    Qfile.close();
}

void finalGdelete()
{
    finalDelete<Permission>(Gpermissions.returnHead());
    finalDelete<Tag>(Gtags.returnHead());
    finalDelete<User>(Gusers.returnHead());
    finalDelete<Question>(Gquestions.returnHead());
}