#include "Users.h"
#include "Question.h"
#include "FourChoice.h"
#include "Descriptive.h"

using namespace std;

template <class T>
struct Node
{
    T *data;
    Node *next;
    Node(T *data) : data(data), next(NULL) {}
};

template <class T>
class linkedList
{
private:
    Node<T> *head = NULL;

public:
    linkedList() { head = NULL; }
    void insertNode(T *);
    void printList();
    void deleteNode(int);
};

template <class T>
void linkedList<T>::insertNode(T *data)
{

    Node<T> *newNode = new Node<T>(data);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    Node<T> *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

template <class T>
void linkedList<T>::printList()
{
    Node<T> *temp = head;

    if (head == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    while (temp != NULL)
    {
        temp->data->print();
        temp = temp->next;
    }
}

template <class T>
void linkedList<T>::deleteNode(int nodeOffset)
{
    Node<T> *temp1 = head, *temp2 = NULL;
    int ListLen = 0;

    if (head == NULL)
    {
        return;
    }

    while (temp1 != NULL)
    {
        temp1 = temp1->next;
        ListLen++;
    }

    if (ListLen < nodeOffset)
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

int main()
{
    linkedList<Question> list;

    list.insertNode(new FourChoice("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"), "a", "b", "c", "d", '0'));
    list.insertNode(new FourChoice("1", {1, 1, 1, 1, 1, 1}, User("1", "1", "1"), "A", "B", "C", "D", 'E'));
    list.insertNode(new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0")));
    list.insertNode(new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0")));

    cout << "Elements of the list are: ";

    list.printList();
    cout << endl;

    list.deleteNode(2);

    cout << "Elements of the list are: ";
    list.printList();
    cout << endl;

    return 0;
}