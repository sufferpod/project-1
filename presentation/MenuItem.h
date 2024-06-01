#pragma once
#include <iostream>
#include "FourChoice.h"
#include "Descriptive.h"
using namespace std;

void loginPrompt()
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
}

void createDescriptiveQ()
{
    cin.ignore();
    string question;
    cout << "Enter the Question: \n";
    getline(cin, question);
    DateTime temp;
    cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
    cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
    Descriptive::create(question, temp, *Auth::whoami());
}

void editDescriptiveQ()
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
}

void printDQ()
{
    Question *x = new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"));
    x->printAll();
    delete x;
}

void PrintOneDescriptive()
{
    int ID;
    cout << " Enter the ID of the Question you want to print: \n";
    cin >> ID;
    questions[ID]->print();
}

void createFourChoiceQ()
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
}

void editFourChoiceQ()
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
}

void printFQ()
{

    Question *x = new FourChoice("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"), "a", "b", "c", "d", '0');
    x->printAll();
    delete x;
}

void PrintOneFourChoice()
{
    int ID;
    cout << " Enter the ID of the Question you want to print: \n";
    cin >> ID;
    questions[ID]->print();
}

void printAllQ()
{
    for (int i = 0; questions[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        questions[i]->print();
        cout << "---------------------------------\n";
    }
}

void addTag()
{
    string temp;
    cout << "Enter the Tag you want to add: \n";
    cin.ignore();
    getline(cin, temp);
    Tag::create(temp);
}

void addUser()
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

addPermission2User()
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
}