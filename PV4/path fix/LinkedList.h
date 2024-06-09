#pragma once
#include "Structs.h"
using namespace std;

template <class T>
class linkedList
{
    friend void unLoadUsers();
    friend void unLoadQuestions();

private:
    Node<T> *head;
    Node<T> *tail;

public:
    linkedList()
    {
        head = NULL;
        tail = NULL;
    }
    Node<T> *returnHead() { return head; }
    void append(T *);
    T *give(int);
    void remove(int);
};

template <class T>
void linkedList<T>::append(T *data)
{

    Node<T> *newNode = new Node<T>(data);
    if (head == NULL)
    {
        head = newNode;
        tail = head;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

template <class T>
T *linkedList<T>::give(int ID)
{
    int Depth = 0;
    Node<T> *temp1 = head;
    while (temp1 != NULL)
    {
        temp1 = temp1->next;
        Depth++;
    }

    if (Depth < ID || head == NULL)
    {
        return NULL;
    }

    temp1 = head;

    if (ID == 0 && head != NULL)
    {
        return head->data;
    }

    while (ID-- > 0)
    {
        if (temp1->next == NULL)
            return NULL;
        temp1 = temp1->next;
    }
    return temp1->data;
}

template <class T>
void linkedList<T>::remove(int nodeOffset)
{
    Node<T> *temp1 = head, *temp2 = NULL;
    int Depth = 0;

    while (temp1 != NULL)
    {
        temp1 = temp1->next;
        Depth++;
    }

    if (Depth < nodeOffset || head == NULL)
    {
        return;
    }

    temp1 = head;

    if (nodeOffset == 1)
    {
        head = head->next;
        delete temp1;
        return;
    }

    while (nodeOffset-- > 1)
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp2->next = temp1->next;
    delete temp1;
}