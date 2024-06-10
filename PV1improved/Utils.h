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

template <typename T>
void finalDelete(T *globalArray[])
{
    for (int i = 0; globalArray[i] != NULL; i++)
        delete globalArray[i];
}

void loadUsers()
{
    Gusers[0] = new User("admin", "admin", "123456");
    for (int i = 0; Gpermissions[i] != NULL; i++)
    {
        Gusers[0]->addpermission(Gpermissions[i]);
    }
    Auth::login("admin", "123456");
    fstream Userfile("/home/suffer/project 1/PV1improved/Users.txt", ios::in);
    string n, un, pa, permend;
    int u = 1;
    while (getline(Userfile, n))
    {
        Permission *perms[10] = {NULL};
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

        for (int i = 0; perms[i] != NULL; i++)
        {
            Gusers[u]->addpermission(perms[i]);
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
    fstream Qfile("/home/suffer/project 1/PV1improved/Questions.txt", ios::in);
    string Qtype;
    while (getline(Qfile, Qtype))
    {
        string question, n, un, pa;
        bool pub;
        DateTime temp;
        Qfile >> pub;
        Qfile.ignore();
        getline(Qfile, question);
        Qfile >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
        Qfile.ignore();
        getline(Qfile, n);
        getline(Qfile, un);
        getline(Qfile, pa);
        Auth::login(un, pa);
        if (Qtype == "descriptive")
            Descriptive::create(question, temp, User(n, un, pa));
        else
        {
            string A, B, C, D;
            char answer;
            getline(Qfile, A);
            getline(Qfile, B);
            getline(Qfile, C);
            getline(Qfile, D);
            Qfile >> answer;
            FourChoice::create(question, temp, User(n, un, pa), A, B, C, D, answer);
        }
        Auth::logout();
    }
    Qfile.close();
}

void unLoadUsers()
{
    fstream Userfile("/home/suffer/project 1/PV1improved/Users.txt", ios::out | ios::trunc);
    for (int i = 1; Gusers[i] != NULL; i++)
    {
        Userfile << Gusers[i]->name << endl
                 << Gusers[i]->username << endl
                 << Gusers[i]->password << endl;
        for (int j = 0; Gusers[i]->permissions[i] != NULL; j++)
        {
            Userfile << Gusers[i]->permissions[j]->viewTitle() << endl;
        }
        Userfile << "permend";
        if (Gusers[i + 1] != NULL)
            Userfile << endl;
    }
    Userfile.close();
}

void unLoadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV1improved/Questions.txt", ios::out | ios::trunc);
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        if (Gquestions[i]->TypeBack() == "descriptive")
        {
            Qfile << Gquestions[i]->TypeBack() << endl
                  << Gquestions[i]->isPublished << endl;
            Qfile << Gquestions[i]->question
                  << endl;
            Qfile << Gquestions[i]->createdAt.year << ' ' << Gquestions[i]->createdAt.month << ' '
                  << Gquestions[i]->createdAt.day << ' ' << Gquestions[i]->createdAt.hour << ' '
                  << Gquestions[i]->createdAt.minute << ' ' << Gquestions[i]->createdAt.second
                  << endl;
            Qfile << Gquestions[i]->user.name << endl
                  << Gquestions[i]->user.username << endl
                  << Gquestions[i]->user.password;
            if (Gquestions[i + 1] != NULL)
                Qfile << endl;
        }
        else
        {
            FourChoice *temp = dynamic_cast<FourChoice *>(Gquestions[i]);
            Qfile << Gquestions[i]->TypeBack() << endl
                  << Gquestions[i]->isPublished << endl;
            Qfile << Gquestions[i]->question
                  << endl;
            Qfile << Gquestions[i]->createdAt.year << ' ' << Gquestions[i]->createdAt.month << ' '
                  << Gquestions[i]->createdAt.day << ' ' << Gquestions[i]->createdAt.hour << ' '
                  << Gquestions[i]->createdAt.minute << ' ' << Gquestions[i]->createdAt.second
                  << endl;
            Qfile << Gquestions[i]->user.name << endl
                  << Gquestions[i]->user.username << endl
                  << Gquestions[i]->user.password << endl;
            Qfile << temp->A << endl
                  << temp->B << endl
                  << temp->C << endl
                  << temp->D << endl
                  << temp->answer;
            if (Gquestions[i + 1] != NULL)
                Qfile << endl;
        }
    }
    Qfile.close();
}

void finalGdelete()
{
    finalDelete<Permission>(Gpermissions);
    finalDelete<Tag>(Gtags);
    finalDelete<User>(Gusers);
    finalDelete<Question>(Gquestions);
}