// AmirSadra Charmforushan
// Mobina Miri
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
    int choice;
    while (true)
    {
        cout << "* Login(1)\n"
             << "* view All Questions(2)\n"
             << "* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
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
        case 2:
            printAllQ();
            break;
        }
        if (choice == 0)
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

    int choice;
    while (true)
    {
        cout << "\t* Question Menu(1)\n"
             << "\t* Tag Menu(2)\n"
             << "\t* User Menu(3)\n"
             << "\t* view All Questions(4)\n"
             << "\t* Logout(0)\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            questionMenu();
            break;
        case 2:
            tagMenu();
            break;
        case 3:
            userMenu();
            break;
        case 4:
            printAllQ();
            break;
        }
        if (choice == 0)
        {
            Auth::logout();
            clear();
            break;
        }
    }
}

void questionMenu()
{
    int choice;
    while (true)
    {
        cout << "Question Menu\n";
        cout << "\t* Create Descriptive Question(1)\n"
             << "\t* Edit Descriptive Question(2)\n"
             << "\t* Add Answer to Descriptive Question(3)\n"
             << "\t* List of Descriptive Questions with ID(4)\n"
             << "\t* Print Descriptive Question(5)\n"
             << "\t* Create FourChoice Question(6)\n"
             << "\t* Edit FourChoice Question(7)\n"
             << "\t* List of FourChoice Questions with ID(8)\n"
             << "\t* Print FourChoice Question(9)\n"
             << "\t* Add Tag to Question(10)\n"
             << "\t* Publish a Question(11)\n"
             << "\t* Unpublish a Question(12)\n"
             << "\t* Delete a Question(13)\n"
             << "\t* view All Questions(14)\n"
             << "\t* Exit(0)\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            createDescriptiveQ();
            break;
        case 2:
            editDescriptiveQ();
            break;
        case 3:
            addAnswertoDQ();
            break;
        case 4:
            printDQ();
            break;
        case 5:
            PrintOneDescriptive();
            break;
        case 6:
            createFourChoiceQ();
            break;
        case 7:
            editFourChoiceQ();
            break;
        case 8:
            printFQ();
            break;
        case 9:
            PrintOneFourChoice();
            break;
        case 10:
            addTagtoQuestion();
            break;
        case 11:
            publishQuestion();
            break;
        case 12:
            unPublishQuestion();
            break;
        case 13:
            deleteQuestion();
            break;
        case 14:
            printAllQ();
            break;
        }
        if (choice == 0)
        {
            clear();
            break;
        }
    }
}

void tagMenu()
{
    int choice;
    while (true)
    {
        cout << "Tag Menu\n";
        cout << "\t* List of Tags with ID(1)\n"
             << "\t* Create New Tag(2)\n"
             << "\t* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            Tag::printAll();
            break;
        case 2:
            addTag();
            break;
        }
        if (choice == 0)
        {
            clear();
            break;
        }
    }
}

void userMenu()
{
    int choice;
    while (true)
    {
        cout << "User Menu\n";
        cout << "\t* List of Users with ID(1)\n"
             << "\t* Create New User(2)\n"
             << "\t* Add permission to a user(3)\n"
             << "\t* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            User::printAll();
            break;
        case 2:
            addUser();
            break;
        case 3:
            addPermission2User();
            break;
        }
        if (choice == 0)
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
        Permission::create(basicperm[i]);
    }
    loadUsers();
    loadQuestions();
}

void unboot()
{
    unLoadUsers();
    unLoadQuestions();
    finalGdelete();
}