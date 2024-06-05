#include <iostream>
#include <ctype.h>
#include "Structs.h"
#include "Permission.h"
#include "Users.h"
#include "Auth.h"
#include "Tag.h"
#include "Question.h"
#include "FourChoice.h"
#include "Descriptive.h"
#include "MenuItem.h"
#include "Utils.h"

using namespace std;

void boot();
void loginTMenu();
void loginFMenu();
void questionMenu();
void tagMenu();
void userMenu();
void unboot();

int main()
{
    boot();
    if (Auth::whoami())
        loginTMenu();
    else
        loginFMenu();
    unboot();
    return 0;
}

void loginFMenu()
{
    char choice;
    while (true)
    {
        cout << "* Login(L)\n"
             << "* view All Questions(V)\n"
             << "* Exit(X)\n";

        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        switch (choice)
        {
        case 'l':
        {
            string un, pa;
            cout << "Enter UserName:\n";
            getline(cin, un);
            cout << "Enter Password:\n";
            getline(cin, pa);
            if (Auth::login(un, pa))
                loginTMenu();
            else
                cout << "User not valid\n";
            break;
        }
        case 'v':
            printAllQ();
            break;
        }
        if (choice == 'x')
        {
            clear();
            break;
        }
    }
}

void loginTMenu()
{
    cout << "----------------------------------\n"
         << "Hello " << Auth::whoami()->myName() << "!\n"
         << "----------------------------------\n";

    char choice;
    while (true)
    {
        cout << "\t* Question Menu(Q)\n"
             << "\t* Tag Menu(T)\n"
             << "\t* User Menu(U)\n"
             << "\t* view All Questions(V)\n"
             << "\t* Logout(X)\n";
        cin >> choice;
        choice = tolower(choice);
        switch (choice)
        {
        case 'q':
            questionMenu();
            break;
        case 't':
            tagMenu();
            break;
        case 'u':
            userMenu();
            break;
        case 'v':
            printAllQ();
            break;
        }
        if (choice == 'x')
        {
            Auth::logout();
            clear();
            break;
        }
    }
}

void questionMenu()
{
    char choice;
    while (true)
    {
        cout << "Question Menu\n";
        cout << "\t* Create Descriptive Question(C)\n"
             << "\t* Edit Descriptive Question(E)\n"
             << "\t* List of Descriptive Questions with ID(D)\n"
             << "\t* Print Descriptive Question(P)\n"
             << "\t* Create FourChoice Question(U)\n"
             << "\t* Edit FourChoice Question(H)\n"
             << "\t* List of FourChoice Questions with ID(F)\n"
             << "\t* Print FourChoice Question(K)\n"
             << "\t* view All Questions(V)\n"
             << "\t* Exit(X)\n";
        cin >> choice;
        choice = tolower(choice);
        switch (choice)
        {
        case 'c':
            createDescriptiveQ();
            break;
        case 'e':
            editDescriptiveQ();
            break;
        case 'd':
        {
            printDQ();
            break;
        }
        case 'p':
            PrintOneDescriptive();
            break;
        case 'u':
            createFourChoiceQ();
            break;
        case 'h':
            editFourChoiceQ();
            break;
        case 'f':
            printFQ();
            break;
        case 'k':
            PrintOneFourChoice();
            break;
        case 'v':
            printAllQ();
            break;
        }
        if (choice == 'x')
        {
            clear();
            break;
        }
    }
}

void tagMenu()
{
    char choice;
    while (true)
    {
        cout << "Tag Menu\n";
        cout << "\t*List of Tags with ID(L)\n"
             << "\t*Create New Tag(T)\n"
             << "\t* Exit(X)\n";

        cin >> choice;
        choice = tolower(choice);
        switch (choice)
        {
        case 'l':
            Tag::printAll();
            break;
        case 't':
            addTag();
            break;
        }
        if (choice == 'x')
        {
            clear();
            break;
        }
    }
}

void userMenu()
{
    char choice;
    while (true)
    {
        cout << "User Menu\n";
        cout << "\t*List of Users with ID(L)\n"
             << "\t*Create New User(U)\n"
             << "\t*Add permission to a user(P)\n"
             << "\t* Exit(X)\n";

        cin >> choice;
        choice = tolower(choice);
        switch (choice)
        {
        case 'l':
            User::printAll();
            break;
        case 'u':
            addUser();
            break;
        case 'p':
            addPermission2User();
            break;
        }
        if (choice == 'x')
        {
            clear();
            break;
        }
    }
}

void boot()
{

    for (int i = 0; i < 5; i++)
    {
        Gpermissions.append(new Permission(basicperm[i]));
    }
    loadUsers();
}

void unboot()
{
    unLoadUsers();
    unLoadQuestions();
    finalGdelete();
}