#pragma once
#include <iostream>
#include "Users.h"
#include "FourChoice.h"
#include "Descriptive.h"
using namespace std;

void printAllQ()
{
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        if (Gquestions[i]->pubBack())
            Gquestions[i]->print();
        else
            cout << "Not published\n";
        cout << "---------------------------------\n";
    }
}

void createDescriptiveQ()
{
    cin.clear();
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
    Gquestions[ID]->edit(question, temp, *Auth::whoami());
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
    Gquestions[ID]->print();
}

void createFourChoiceQ()
{
    cin.clear();
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
    Gquestions[ID]->edit(question, temp, *Auth::whoami(), a, b, c, d, ans);
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
    cout << "Enter the ID of the Question you want to print: \n";
    cin >> ID;
    Gquestions[ID]->print();
}

void addTagtoQuestion()
{
    int IDQ, IDT;
    cout << "Enter the ID of the Question you want to add to: \n";
    cin >> IDQ;
    cout << "Enter the ID of the Tag you want to add: \n";
    cin >> IDT;
    Gquestions[IDQ]->addTag(Gtags[IDT]);
}

void publishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Publish: \n";
    cin >> ID;
    Gquestions[ID]->publish();
}

void unPublishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Unpublish: \n";
    cin >> ID;
    Gquestions[ID]->unpublish();
}

void deleteQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Delete: \n";
    cin >> ID;
    Question::remove(ID);
}

void addTag()
{
    string temp;
    cout << "Enter the Tag you want to add: \n";
    getline(cin, temp);
    Tag::create(temp);
}

void addUser()
{
    cin.clear();
    string n, un, pa;
    cout << "Enter Name:\n";
    getline(cin, n);
    cout << "Enter UserName:\n";
    getline(cin, un);
    cout << "Enter Password:\n";
    getline(cin, pa);
    User::create(n, un, pa, Auth::whoami());
}

void addPermission2User()
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
    Gusers[ID]->addpermission(Gpermissions[p - 1]);
}