// AmirSadra Charmforushan
// Mobina Miri
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <fstream>

using namespace std;

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

    ~linkedList()
    {
        while (head != NULL)
        {
            Node<T> *Next = head->next;
            delete head;
            head = Next;
        }
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

class Permission
{
private:
    string title;

public:
    Permission(string per) : title(per) {}
    static Permission *create(string ti);
    void print();
    string viewTitle();
};

string basicperm[5]{
    "add-descriptive-question", "add-four-choice-question",
    "edit-descriptive-question", "edit-four-choice-question",
    "add-user"};
linkedList<Permission> Gpermissions;

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    Node<Permission> *temp = Gpermissions.returnHead();
    while (temp != NULL)
    {
        if (temp->data->title == x->title)
            return NULL;
        temp = temp->next;
    }
    Gpermissions.append(x);
    return x;
}

void Permission::print()
{
    cout << title << endl;
}

string Permission::viewTitle()
{
    return title;
}

class User
{
    friend void unLoadUsers();
    friend void unLoadQuestions();

private:
    string name, username, password;
    Permission *permissions[100] = {NULL};

public:
    User(string n, string un, string pa) : name(n), username(un), password(pa) {}
    static User *create(string, string, string, User *);
    void addpermission(Permission *permission);
    void print();
    static void printAll();
    bool checkAuth(string, string);
    bool checkPermTi(string);
    string myName();
};

linkedList<User> Gusers;

User *User::create(string n, string un, string pa, User *ami)
{
    if (ami->checkPermTi("add-user"))
    {
        if (!ami->checkAuth(un, pa))
        {
            User *x = new User(n, un, pa);
            Gusers.append(x);
            return x;
        }
    }
    else
    {
        cout << "You don't have the \"add-user\" permission\n";
        return NULL;
    }
    return NULL;
}

void User::addpermission(Permission *permission)
{
    int i = 0;
    for (; permissions[i] != NULL; i++)
    {
        if (permissions[i] == permission)
            return;
    }
    permissions[i] = permission;
}

void User::print()
{
    cout << "Name: " << name
         << "\nUser name: " << username
         << "\nPassword: " << password
         << "\nPermissions: \n";
    for (int i = 0; permissions[i] != NULL; i++)
        permissions[i]->print();
}

void User::printAll()
{
    Node<User> *temp = Gusers.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        cout << "ID: " << i << endl;
        temp->data->print();
        temp = temp->next;
    }
}

bool User::checkAuth(string un, string pa)
{
    if (username == un && password == pa)
        return true;
    return false;
}

bool User::checkPermTi(string ti)
{
    for (int i = 0; permissions[i] != NULL; i++)
    {
        if (permissions[i]->viewTitle() == ti)
            return true;
    }
    return false;
}

string User::myName()
{
    return username;
}

class Auth
{
private:
    inline static User *auth = NULL;

public:
    static User *login(string username, string password);
    static void logout() { auth = NULL; }
    static User *whoami() { return auth; }
};

User *Auth::login(string username, string password)
{
    Node<User> *temp = Gusers.returnHead();
    while (temp != NULL)
    {
        if (temp->data->checkAuth(username, password))
        {
            auth = temp->data;
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}

class Tag
{
private:
    string title;

public:
    Tag(string ti) : title(ti) {}
    static Tag *create(string ti);
    string veiwTitle();
    void print();
    static void printAll();
};

linkedList<Tag> Gtags;

Tag *Tag::create(string ti)
{
    Node<Tag> *temp = Gtags.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        if (temp->data->veiwTitle() == ti)
            return NULL;
        temp = temp->next;
    }
    Tag *tempT = new Tag(ti);
    Gtags.append(tempT);
    return tempT;
}

string Tag::veiwTitle()
{
    return title;
}

void Tag::print()
{
    cout << title << endl;
}

void Tag::printAll()
{
    cout << "tags: \n";
    Node<Tag> *temp = Gtags.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        cout << "ID: " << i << endl;
        temp->data->print();
        temp = temp->next;
    }
    cout << endl;
}

class Question
{
    friend void unLoadQuestions();

public:
    Question(string Qu, string ty, DateTime ti, User us) : question(Qu), type(ty), createdAt(ti), user(us) {}
    void publish() { isPublished = true; }
    void unpublish() { isPublished = false; }
    virtual void print() = 0;
    virtual void printAll() = 0;
    virtual Question *edit(string, DateTime, User, string, string, string, string, char) = 0;
    virtual Question *edit(string, DateTime, User) = 0;
    void addTag(Tag *);
    bool pubBack();
    string TypeBack();

protected:
    string question;
    string type;
    DateTime createdAt;
    User user;
    Tag *tags[100] = {NULL};
    bool isPublished = false;
};

void Question::addTag(Tag *tag)
{
    int i = 0;
    for (; tags[i] != NULL; i++)
    {
        if (tags[i] == tag)
            return;
    }
    tags[i] = tag;
}

bool Question::pubBack()
{
    return isPublished;
}

string Question::TypeBack()
{
    return type;
}

linkedList<Question> Gquestions;

class Descriptive : public Question
{
    friend void unLoadQuestions();

public:
    Descriptive(string qu, DateTime cr, User us) : Question(qu, "descriptive", cr, us) {}
    void AddAnswer(string ans);
    void print();
    void printAll();
    static Descriptive *create(string question, DateTime createdAt, User user);
    Question *edit(string, DateTime, User, string, string, string, string, char);
    Question *edit(string question, DateTime createdAt, User user) override;

private:
    string answer;
};

Descriptive *Descriptive::create(string question, DateTime createdAt, User user)
{
    if (Auth::whoami()->checkPermTi("add-descriptive-question"))
    {
        Descriptive *x = new Descriptive(question, createdAt, user);
        x->publish();
        Gquestions.append(x);
        return x;
    }
    else
    {
        cout << "You don't have the \"add-descriptive-question\" permission\n";
        return NULL;
    }
    return NULL;
}

Question *Descriptive::edit(string, DateTime, User, string, string, string, string, char) { return NULL; }
Question *Descriptive::edit(string question, DateTime createdAt, User user)
{
    if (Auth::whoami()->checkPermTi("edit-descriptive-question"))
    {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        return this;
    }
    else
    {
        cout << "You don't have the \"edit-descriptive-question\" permission\n";
        return NULL;
    }
    return NULL;
}

void Descriptive::AddAnswer(string ans)
{
    answer = ans;
}

void Descriptive::print()
{
    cout << "Question: " << question << endl
         << "Answer: " << answer << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: " << user.myName() << endl;
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
}

void Descriptive::printAll()
{
    Node<Question> *temp = Gquestions.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        if (temp->data->TypeBack() == "descriptive")
        {
            if (temp->data->pubBack())
            {
                cout << "ID : " << i << endl;
                temp->data->print();
            }
            else
                cout << "ID: " << i << "Not published\n";
        }
        temp = temp->next;
    }
}

class FourChoice : public Question
{
    friend void unLoadQuestions();

public:
    FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans) : Question(Qu, "four-choice", ti, us), A(a), B(b), C(c), D(d), answer(ans) {}
    void print();
    void printAll();
    Question *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) override;
    Question *edit(string, DateTime, User);
    static FourChoice *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("add-four-choice-question"))
    {
        FourChoice *x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        x->publish();
        Gquestions.append(x);
        return x;
    }
    else
    {
        cout << "You don't have the \"add-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
}

Question *FourChoice::edit(string, DateTime, User) { return NULL; }
Question *FourChoice::edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("edit-four-choice-question"))
    {
        this->question = question;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->answer = answer;
        return this;
    }
    else
    {
        cout << "You don't have the \"edit-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
}

void FourChoice::print()
{
    cout << "Question: " << question << endl
         << "A) " << A << endl
         << "B) " << B << endl
         << "C) " << C << endl
         << "D) " << D << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: " << user.myName() << endl;
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
}

void FourChoice::printAll()
{
    Node<Question> *temp = Gquestions.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        if (temp->data->TypeBack() == "four-choice")
        {
            if (temp->data->pubBack())
            {
                cout << "ID : " << i << endl;
                temp->data->print();
            }
            else
                cout << "ID : " << i << "Not published\n";
        }
        temp = temp->next;
    }
}

template <class T>
void finalDelete(Node<T> *);
void boot();
void clear();
void printAllQ();
void loginTMenu();
void loginFMenu();
void createDescriptiveQ();
void editDescriptiveQ();
void printDQ();
void PrintOneDescriptive();
void createFourChoiceQ();
void editFourChoiceQ();
void printFQ();
void PrintOneFourChoice();
void addTagtoQuestion();
void publishQuestion();
void unPublishQuestion();
void deleteQuestion();
void questionMenu();
void addTag();
void tagMenu();
void addUser();
void addPermission2User();
void userMenu();
void loadUsers();
void loadQuestions();
void unLoadUsers();
void unLoadQuestions();
void finalGdelete();
void unboot();

int main()
{
    boot();
    if (Auth::whoami())
        loginTMenu();
    else
        loginFMenu();
    unboot();
    return 0;
}

void loginFMenu()
{
    int choice;
    while (true)
    {
        cout << "* Login(1)\n"
             << "* view All Questions(2)\n"
             << "* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            string un, pa;
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
        case 2:
            printAllQ();
            break;
        }
        if (choice == 0)
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

    int choice;
    while (true)
    {
        cout << "\t* Question Menu(1)\n"
             << "\t* Tag Menu(2)\n"
             << "\t* User Menu(3)\n"
             << "\t* view All Questions(4)\n"
             << "\t* Logout(0)\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            questionMenu();
            break;
        case 2:
            tagMenu();
            break;
        case 3:
            userMenu();
            break;
        case 4:
            printAllQ();
            break;
        }
        if (choice == 0)
        {
            Auth::logout();
            clear();
            break;
        }
    }
}

void questionMenu()
{
    int choice;
    while (true)
    {
        cout << "Question Menu\n";
        cout << "\t* Create Descriptive Question(1)\n"
             << "\t* Edit Descriptive Question(2)\n"
             << "\t* List of Descriptive Questions with ID(3)\n"
             << "\t* Print Descriptive Question(4)\n"
             << "\t* Create FourChoice Question(5)\n"
             << "\t* Edit FourChoice Question(6)\n"
             << "\t* List of FourChoice Questions with ID(7)\n"
             << "\t* Print FourChoice Question(8)\n"
             << "\t* Add Tag to Question(9)\n"
             << "\t* Publish a Question(10)\n"
             << "\t* Unpublish a Question(11)\n"
             << "\t* Delete a Question(12)\n"
             << "\t* view All Questions(13)\n"
             << "\t* Exit(0)\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            createDescriptiveQ();
            break;
        case 2:
            editDescriptiveQ();
            break;
        case 3:
            printDQ();
            break;
        case 4:
            PrintOneDescriptive();
            break;
        case 5:
            createFourChoiceQ();
            break;
        case 6:
            editFourChoiceQ();
            break;
        case 7:
            printFQ();
            break;
        case 8:
            PrintOneFourChoice();
            break;
        case 9:
            addTagtoQuestion();
            break;
        case 10:
            publishQuestion();
            break;
        case 11:
            unPublishQuestion();
            break;
        case 12:
            deleteQuestion();
            break;
        case 13:
            printAllQ();
            break;
        }
        if (choice == 0)
        {
            clear();
            break;
        }
    }
}

void tagMenu()
{
    int choice;
    while (true)
    {
        cout << "Tag Menu\n";
        cout << "\t*List of Tags with ID(1)\n"
             << "\t*Create New Tag(2)\n"
             << "\t* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            Tag::printAll();
            break;
        case 2:
            addTag();
            break;
        }
        if (choice == 0)
        {
            clear();
            break;
        }
    }
}

void userMenu()
{
    int choice;
    while (true)
    {
        cout << "User Menu\n";
        cout << "\t*List of Users with ID(1)\n"
             << "\t*Create New User(2)\n"
             << "\t*Add permission to a user(3)\n"
             << "\t* Exit(0)\n";

        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            User::printAll();
            break;
        case 2:
            addUser();
            break;
        case 3:
            addPermission2User();
            break;
        }
        if (choice == 0)
        {
            clear();
            break;
        }
    }
}

void boot()
{
    for (int i = 0; i < 5; i++)
    {
        Permission::create(basicperm[i]);
    }
    loadUsers();
    loadQuestions();
}

void unboot()
{
    unLoadUsers();
    unLoadQuestions();
    finalGdelete();
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
    Gquestions.give(ID)->edit(question, temp, *Auth::whoami());
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
    Gquestions.give(ID)->print();
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
    Gquestions.give(ID)->edit(question, temp, *Auth::whoami(), a, b, c, d, ans);
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
    Gquestions.give(ID)->print();
}

void addTagtoQuestion()
{
    int IDQ, IDT;
    cout << "Enter the ID of the Question you want to add to: \n";
    cin >> IDQ;
    cout << "Enter the ID of the Tag you want to add: \n";
    cin >> IDT;
    Gquestions.give(IDQ)->addTag(Gtags.give(IDT));
}

void publishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Publish: \n";
    cin >> ID;
    Gquestions.give(ID)->publish();
}

void unPublishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Unpublish: \n";
    cin >> ID;
    Gquestions.give(ID)->unpublish();
}

void printAllQ()
{
    Node<Question> *temp = Gquestions.returnHead();
    for (int i = 0; temp != NULL; i++)
    {
        cout << "ID: " << i << endl;
        if (temp->data->pubBack())
            temp->data->print();
        else
            cout << "Not published\n";
        cout << "---------------------------------\n";
        temp = temp->next;
    }
}

void deleteQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Delete: \n";
    cin >> ID;
    Gquestions.remove(ID);
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
    Gusers.give(ID)->addpermission(Gpermissions.give(p - 1));
}

void clear()
{
#ifdef __linux__
    system("clear");
#elif _WIN64
    system("cls");
#endif
}

template <class T>
void finalDelete(Node<T> *head)
{
    while (head != NULL)
    {
        Node<T> *Next = head->next;
        delete head->data;
        head = Next;
    }
}

void loadUsers()
{
    Gusers.append(new User("admin", "admin", "123456"));
    Node<User> *temp = Gusers.returnHead();
    Node<Permission> *tempP = Gpermissions.returnHead();
    while (tempP != NULL)
    {
        temp->data->addpermission(tempP->data);
        tempP = tempP->next;
    }
    Auth::login("admin", "123456");
    fstream Userfile("Users.txt", ios::in);
    string n, un, pa, permend;
    while (getline(Userfile, n))
    {
        Permission *perms[10] = {NULL};
        getline(Userfile, un);
        getline(Userfile, pa);
        User::create(n, un, pa, Auth::whoami());
        for (int i = 0;; i++)
        {
            getline(Userfile, permend);
            if (permend == "permend")
            {
                break;
            }
            perms[i] = new Permission(permend);
        }

        temp = temp->next;
        for (int i = 0; perms[i] != NULL; i++)
        {
            temp->data->addpermission(perms[i]);
        }
        for (int i = 0; perms[i] != NULL; i++)
        {
            delete perms[i];
        }
    }
    Auth::logout();
    Userfile.close();
}

void loadQuestions()
{
    fstream Qfile("Questions.txt", ios::in);
    string Qtype;
    while (getline(Qfile, Qtype))
    {
        string question, n, un, pa;
        bool pub;
        DateTime temp;
        Qfile >> pub;
        Qfile.ignore();
        getline(Qfile, question);
        Qfile >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
        Qfile.ignore();
        getline(Qfile, n);
        getline(Qfile, un);
        getline(Qfile, pa);
        Auth::login(un, pa);
        if (Qtype == "descriptive")
            Descriptive::create(question, temp, User(n, un, pa));
        else
        {
            string A, B, C, D;
            char answer;
            getline(Qfile, A);
            getline(Qfile, B);
            getline(Qfile, C);
            getline(Qfile, D);
            Qfile >> answer;
            FourChoice::create(question, temp, User(n, un, pa), A, B, C, D, answer);
        }
        Auth::logout();
    }
    Qfile.close();
}

void unLoadUsers()
{
    fstream Userfile("Users.txt", ios::out | ios::trunc);
    Node<User> *temp = Gusers.returnHead()->next;
    for (int i = 0; temp != NULL; i++)
    {
        Userfile << temp->data->name << endl
                 << temp->data->username << endl
                 << temp->data->password << endl;
        for (int j = 0; temp->data->permissions[i] != NULL; j++)
        {
            Userfile << temp->data->permissions[j]->viewTitle() << endl;
        }
        Userfile << "permend";
        if (temp != Gusers.tail)
            Userfile << endl;
        temp = temp->next;
    }
    Userfile.close();
}

void unLoadQuestions()
{
    fstream Qfile("Questions.txt", ios::out | ios::trunc);
    Node<Question> *temp = Gquestions.returnHead();
    while (temp != NULL)
    {
        if (temp->data->TypeBack() == "descriptive")
        {
            Qfile << temp->data->TypeBack() << endl
                  << temp->data->isPublished << endl;
            Qfile << temp->data->question
                  << endl;
            Qfile << temp->data->createdAt.year << ' ' << temp->data->createdAt.month << ' '
                  << temp->data->createdAt.day << ' ' << temp->data->createdAt.hour << ' '
                  << temp->data->createdAt.minute << ' ' << temp->data->createdAt.second
                  << endl;
            Qfile << temp->data->user.name << endl
                  << temp->data->user.username << endl
                  << temp->data->user.password;
            if (temp != Gquestions.tail)
                Qfile << endl;
        }
        else
        {
            FourChoice *temp2 = dynamic_cast<FourChoice *>(temp->data);
            Qfile << temp->data->TypeBack() << endl
                  << temp->data->isPublished << endl;
            Qfile << temp->data->question
                  << endl;
            Qfile << temp->data->createdAt.year << ' ' << temp->data->createdAt.month << ' '
                  << temp->data->createdAt.day << ' ' << temp->data->createdAt.hour << ' '
                  << temp->data->createdAt.minute << ' ' << temp->data->createdAt.second
                  << endl;
            Qfile << temp->data->user.name << endl
                  << temp->data->user.username << endl
                  << temp->data->user.password << endl;
            Qfile << temp2->A << endl
                  << temp2->B << endl
                  << temp2->C << endl
                  << temp2->D << endl
                  << temp2->answer;
            if (temp != Gquestions.tail)
                Qfile << endl;
        }
        temp = temp->next;
    }
    Qfile.close();
}

void finalGdelete()
{
    finalDelete<Permission>(Gpermissions.returnHead());
    finalDelete<Tag>(Gtags.returnHead());
    finalDelete<User>(Gusers.returnHead());
    finalDelete<Question>(Gquestions.returnHead());
}