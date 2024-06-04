template <class T>
class Node
{
public:
    T data;
    Node *Next;
    Node() : Next(NULL) {}
    Node(T d) : data(d), Next(NULL) {}
};

template <class T>
class linkedList
{
private:
    Node *head;

public:
    Linkedlist() { head = NULL; }
    void insertNode(T);
    void deleteNode(int);
};

void linkedList::deleteNode(int nodeOffset)
{
    Node *temp1 = head, *temp2 = NULL;
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

void linkedList::insertNode(T data)
{
    Node *newNode = new Node(data);
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}