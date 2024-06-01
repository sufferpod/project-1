#include <iostream>
#include "Structs.h"
#include "Permission.h"
#include "Users.h"
#include "Auth.h"
#include "Tag.h"
#include "Question.h"
#include "FourChoice.h"
#include "Descriptive.h"
#include "Utils.h"

using namespace std;

void loginTMenu();
void loginFMenu();
void questionMenu();
void tagMenu();
void userMenu();

int main()
{
    users[0] = new User("admin", "admin", "123456");
    for (int i = 0; Gpermissions[i] != NULL; i++)
    {
        users[0]->addpermission(Gpermissions[i]);
    }
    if (Auth::whoami())
        loginTMenu();
    else
        loginFMenu();
    for (int i = 0; Gpermissions[i] != NULL; i++)
        delete Gpermissions[i];
    for (int i = 0; Gtags[i] != NULL; i++)
        delete Gtags[i];
    for (int i = 0; users[i] != NULL; i++)
        delete users[i];
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

        switch (choice)
        {
        case 'l':
        case 'L':
        {
            string n, un, pa;
            cout << "Enter Name:\n";
            getline(cin, n);
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
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
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
             << "\t* Exit(X)\n";
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
        case 'v':
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
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
        switch (choice)
        {
        case 'c':
        case 'C':
        {
            cin.ignore();
            string question;
            cout << "Enter the Question: \n";
            getline(cin, question);
            DateTime temp;
            cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
            cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            Descriptive::create(question, temp, *Auth::whoami());
            break;
        }
        case 'e':
        case 'E':
        {
            int ID;
            cout << "Enter the ID of the Question you want to edit: \n";
            cin >> ID;
            cin.ignore();
            string question;
            cout << "Enter the new Question: \n";
            getline(cin, question);
            DateTime temp;
            cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
            cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            questions[ID]->edit(question, temp, *Auth::whoami());
            break;
        }
        case 'd':
        case 'D':
        {
            printDQ();
            break;
        }
        case 'p':
        case 'P':
        {
            int ID;
            cout << " Enter the ID of the Question you want to print: \n";
            cin >> ID;
            questions[ID]->print();
            break;
        }
        case 'u':
        case 'U':
        {
            cin.ignore();
            string question;
            cout << "Enter the Question: \n";
            getline(cin, question);
            string a, b, c, d;
            cout << "Enter Options(one on each line): \n";
            getline(cin, a);
            getline(cin, b);
            getline(cin, c);
            getline(cin, d);
            char ans;
            cout << "Enter the correct answer's letter: ";
            cin >> ans;
            DateTime temp;
            cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
            cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            FourChoice::create(question, temp, *Auth::whoami(), a, b, c, d, ans);
            break;
        }
        case 'h':
        case 'H':
        {
            int ID;
            cout << "Enter the ID of the Question you want to edit: \n";
            cin >> ID;
            cin.ignore();
            string question;
            cout << "Enter the Question: \n";
            getline(cin, question);
            string a, b, c, d;
            cout << "Enter Options(one on each line): \n";
            getline(cin, a);
            getline(cin, b);
            getline(cin, c);
            getline(cin, d);
            char ans;
            cout << "Enter the correct answer's letter: ";
            cin >> ans;
            DateTime temp;
            cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
            cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            questions[ID]->edit(question, temp, *Auth::whoami(), a, b, c, d, ans);
            break;
        }
        case 'f':
        case 'F':
            printFQ();
            break;
        case 'k':
        case 'K':
        {
            int ID;
            cout << " Enter the ID of the Question you want to print: \n";
            cin >> ID;
            questions[ID]->print();
            break;
            break;
        }
        case 'v':
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
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
        switch (choice)
        {
        case 'l':
        case 'L':
            Tag::printAll();
            break;
        case 't':
        case 'T':
        {
            string temp;
            cout << "Enter the Tag you want to add: \n";
            cin.ignore();
            getline(cin, temp);
            Tag::create(temp);
            break;
        }
        }
        if (choice == 'x' || choice == 'X')
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
        switch (choice)
        {
        case 'l':
        case 'L':
            User::printAll();
            break;
        case 'u':
        case 'U':
        {
            cin.ignore();
            string n, un, pa;
            cout << "Enter Name:\n";
            getline(cin, n);
            cout << "Enter UserName:\n";
            getline(cin, un);
            cout << "Enter Password:\n";
            getline(cin, pa);
            User::create(n, un, pa, Auth::whoami());
            break;
        }
        case 'p':
        case 'P':
        {
            int ID;
            cout << "enter the ID of the User you want to add permission to: \n";
            cin >> ID;
            int p;
            cout << "What permission do you want to add?\n"
                 << "add-descriptive-question(1)\n"
                 << "add-four-choice-question(2)\n"
                 << "edit-descriptive-question(3)\n"
                 << "edit-four-choice-question(4)\n"
                 << "add-user(5)\n";
            cin >> p;
            users[ID]->addpermission(Gpermissions[p - 1]);
            break;
        }
        }
        if (choice == 'x' || choice == 'X')
        {
            clear();
            break;
        }
    }
}