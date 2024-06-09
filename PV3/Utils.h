#pragma once
#include <fstream>
#include "LinkedList.h"
#include "Permission.h"
#include "Users.h"
#include "Auth.h"
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

// todo load user permitions
void loadUsers()
{
    Gusers.append(new User("admin", "admin", "123456"));
    User *temp = Gusers.give(0);
    for (int i = 0; Gpermissions.give(i) != NULL; i++)
    {
        temp->addpermission(Gpermissions.give(i));
    }
    Auth::login("admin", "123456");
    fstream Userfile("/home/suffer/project 1/PV3/Users.txt", ios::in);
    string n, un, pa, permend;
    int u = 0;
    while (getline(Userfile, n))
    {
        Permission *perms[5] = {NULL};
        getline(Userfile, un);
        getline(Userfile, pa);
        User::create(n, un, pa, Auth::whoami());
        for (int i = 0;; i++)
        {
            getline(Userfile, permend);
            if (permend == "permend")
            {
                break;
            }
            perms[i] = new Permission(permend);
        }

        User *temp = Gusers.give(u);
        for (int i = 0; perms[i] != NULL; i++)
        {
            temp->addpermission(perms[i]);
        }
        for (int i = 0; perms[i] != NULL; i++)
        {
            delete perms[i];
        }
        u++;
    }
    Auth::logout();
    Userfile.close();
}

void loadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV3/Questions.txt", ios::in);
    string Qtype;
    while (getline(Qfile, Qtype))
    {
        string question, n, un, pa;
        DateTime temp;
        if (Qtype == "descriptive")
        {
            getline(Qfile, question);
            Qfile >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            Qfile.ignore();
            getline(Qfile, n);
            getline(Qfile, un);
            getline(Qfile, pa);
            Auth::login(un, pa);
            Descriptive::create(question, temp, User(n, un, pa));
            Auth::logout();
        }
        else
        {
            string A, B, C, D;
            char answer;
            getline(Qfile, question);
            Qfile >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            Qfile.ignore();
            getline(Qfile, n);
            getline(Qfile, un);
            getline(Qfile, pa);
            getline(Qfile, A);
            getline(Qfile, B);
            getline(Qfile, C);
            getline(Qfile, D);
            Qfile >> answer;
            Auth::login(un, pa);
            FourChoice::create(question, temp, User(n, un, pa), A, B, C, D, answer);
            Auth::logout();
        }
    }
    Qfile.close();
}

void unLoadUsers()
{
    fstream Userfile("/home/suffer/project 1/PV3/Users.txt", ios::out | ios::trunc);
    for (int i = 1; Gusers.give(i) != NULL; i++)
    {
        User *temp = Gusers.give(i);
        Userfile << temp->name << endl
                 << temp->username << endl
                 << temp->password << endl;
        for (int i = 0; temp->permissions[i] != NULL; i++)
        {
            Userfile << temp->permissions[i]->viewTitle() << endl;
        }
        Userfile << "permend";
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