#pragma once
#include <iostream>
#include <cstdlib>
#include "question.h"
#include "permission.h"

Permission *globalPermission[4] = {new permission("add-descriptive-question"), new permission("add-four-choice-question"),
                                   new permission("edit-descriptive-question"), new permission("edit-four-choice-question"),
                                   new permission("add-user")};

using namespace std;
void stub();
void login();
bool stup();
void questionMenu();
void tagMenu();
void userMenu();

int main()
{
    char choice;

    while (true)
    {
        cout << "* Login(L)" << endl;
        cout << "* view the Questions(v)" << endl;

        cin >> choice;
        switch (choice)
        {
        case 'l':
        case 'L':
            if (stup())
                login();
            else
                stub();
            break;
        case 'v':
        case 'V':
            stub();
            break;
        }
        system("cls");
    }
    return 0;
}
void stub()
{
}
bool stup()
{
    return 1;
}
void login()
{
    cout << "----------------------------------" << endl
         << "Hello" << stup() << '!'
         << "----------------------------------" << endl;
    char choice;

    while (true)
    {
        cout << "* Question menu(Q)" << endl;
        cout << "* Tag menu(T)" << endl;
        cout << "* User menu(U)" << endl;
        cin >> choice;
        switch (choice)
        {
        case 'Q':
        case 'q':
            questionMenu();
            break;
        case 't':
        case 'T':
            tagMenu();
            break;
        case 'u':
        case 'U':
            userMenu();
            break;
        }
        system("cls");
    }
}