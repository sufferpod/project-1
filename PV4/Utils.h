#pragma once
#include <fstream>
#include "linkedList.h"
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

void loadUsers()
{
    Gusers.append(new User("admin", "admin", "123456"));
    Node<User> *temp = Gusers.returnHead();
    Node<Permission> *tempP = Gpermissions.returnHead();
    while (tempP != NULL)
    {
        temp->data->addpermission(tempP->data);
        tempP = tempP->next;
    }
    Auth::login("admin", "123456");
    fstream Userfile("/home/suffer/project 1/PV4/Users.txt", ios::in);
    string n, un, pa, permend;
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

        temp = temp->next;
        for (int i = 0; perms[i] != NULL; i++)
        {
            temp->data->addpermission(perms[i]);
        }
        for (int i = 0; perms[i] != NULL; i++)
        {
            delete perms[i];
        }
    }
    Auth::logout();
    Userfile.close();
}

void loadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV4/Questions.txt", ios::in);
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
    fstream Userfile("/home/suffer/project 1/PV4/Users.txt", ios::out | ios::trunc);
    Node<User> *temp = Gusers.returnHead()->next;
    for (int i = 0; temp != NULL; i++)
    {
        Userfile << temp->data->name << endl
                 << temp->data->username << endl
                 << temp->data->password << endl;
        for (int j = 0; temp->data->permissions[i] != NULL; j++)
        {
            Userfile << temp->data->permissions[j]->viewTitle() << endl;
        }
        Userfile << "permend";
        if (temp != Gusers.tail)
            Userfile << endl;
        temp = temp->next;
    }
    Userfile.close();
}

void unLoadQuestions()
{
    fstream Qfile("/home/suffer/project 1/PV4/Questions.txt", ios::out | ios::trunc);
    Node<Question> *temp = Gquestions.returnHead();
    while (temp != NULL)
    {
        if (temp->data->TypeBack() == "descriptive")
        {
            Qfile << temp->data->TypeBack() << endl
                  << temp->data->isPublished << endl;
            Qfile << temp->data->question
                  << endl;
            Qfile << temp->data->createdAt.year << ' ' << temp->data->createdAt.month << ' '
                  << temp->data->createdAt.day << ' ' << temp->data->createdAt.hour << ' '
                  << temp->data->createdAt.minute << ' ' << temp->data->createdAt.second
                  << endl;
            Qfile << temp->data->user.name << endl
                  << temp->data->user.username << endl
                  << temp->data->user.password;
            if (temp != Gquestions.tail)
                Qfile << endl;
        }
        else
        {
            FourChoice *temp2 = dynamic_cast<FourChoice *>(temp->data);
            Qfile << temp->data->TypeBack() << endl
                  << temp->data->isPublished << endl;
            Qfile << temp->data->question
                  << endl;
            Qfile << temp->data->createdAt.year << ' ' << temp->data->createdAt.month << ' '
                  << temp->data->createdAt.day << ' ' << temp->data->createdAt.hour << ' '
                  << temp->data->createdAt.minute << ' ' << temp->data->createdAt.second
                  << endl;
            Qfile << temp->data->user.name << endl
                  << temp->data->user.username << endl
                  << temp->data->user.password << endl;
            Qfile << temp2->A << endl
                  << temp2->B << endl
                  << temp2->C << endl
                  << temp2->D << endl
                  << temp2->answer;
            if (temp != Gquestions.tail)
                Qfile << endl;
        }
        temp = temp->next;
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