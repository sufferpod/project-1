#pragma once
struct DateTime
{
    int year, month, day, hour, minute, second;
};

template <class T>
struct Node
{
    T *data;
    Node *next;
    Node(T *data) : data(data), next(NULL) {}
};