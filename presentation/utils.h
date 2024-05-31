#pragma once
#include <cstdlib>
#include "question.h"
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
    printDQ();
    printFQ();
}

void clear()
{
    system("clear");
}