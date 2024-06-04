#include "Users.h"
#include "Question.h"
#include "FourChoice.h"
#include "Descriptive.h"
#include "Structs.h"

using namespace std;

template <class T>
class linkedList
{
private:
    Node<T> *head = NULL;
    Node<T> *tail = NULL;

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
    tail->next = newNode;
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
void linkedList<T>::deleteNode(int ID)
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

    if (ListLen < ID)
    {
        return;
    }

    temp1 = head;

    if (ID == 1)
    {
        head = head->next;
        delete temp1;
        return;
    }

    while (ID-- > 1)
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp2->next = temp1->next;
    delete temp1;
}

int main()
{
    linkedList<Question> Qlist;
    linkedList<User> Ulist;

    Qlist.insertNode(new FourChoice("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0"), "a", "b", "c", "d", '0'));
    Qlist.insertNode(new FourChoice("1", {1, 1, 1, 1, 1, 1}, User("1", "1", "1"), "A", "B", "C", "D", 'E'));
    Qlist.insertNode(new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0")));
    Qlist.insertNode(new Descriptive("0", {0, 0, 0, 0, 0, 0}, User("0", "0", "0")));
    Ulist.insertNode(new User("admin", "admin", "123456"));
    cout
        << "Elements of the list are: \n";

    Qlist.printList();
    cout << endl;

    Qlist.deleteNode(2);

    cout << "Elements of the Qlist are: \n";
    Qlist.printList();
    cout << endl;

    cout << "Elements of the Ulist are: \n";
    Ulist.printList();
    cout << endl;

    return 0;
}