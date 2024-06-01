#pragma once
#include <cstdlib>
#include "Question.h"
#include "FourChoice.h"
#include "Descriptive.h"

void printDQ()
{
    Question *x = new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"));
    x->printAll();
    delete x;
}
void printFQ()
{

    Question *x = new FourChoice("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"), "a", "b", "c", "d", '0');
    x->printAll();
    delete x;
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

void clear()
{
    system("cls");
}