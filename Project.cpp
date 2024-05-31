#include <iostream>
#include <cstdlib>
using namespace std;

struct DateTime
{
    int year, month, day, hour, minute, second;
};

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

Permission *Gpermissions[100] = {new Permission("add-descriptive-question"), new Permission("add-four-choice-question"),
                                 new Permission("edit-descriptive-question"), new Permission("edit-four-choice-question"),
                                 new Permission("add-user"), NULL};

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    int i = 0;
    for (; Gpermissions[i] != NULL; i++)
    {
        if (Gpermissions[i]->title == x->title)
        {
            break;
        }
    }
    if (Gpermissions[i] == NULL)
    {
        Gpermissions[i] = x;
    }
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
User *users[100] = {NULL};
User *User::create(string n, string un, string pa, User *ami)
{
    User *x = new User(n, un, pa);
    if (ami->checkPermTi("add-user"))
    {
        int i = 0;
        for (; users[i] != NULL; i++)
        {
            ;
        }
        if (!ami->checkAuth(un, pa))
        {
            users[i] = x;
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
        if (permissions[i]->viewTitle() == permission->viewTitle())
        {
            break;
        }
    }

    if (permissions[i] == NULL)
    {
        permissions[i] = permission;
    }
}

void User::print()
{
    cout << "Name: " << name
         << "\nUser name: " << username
         << "\nPassword: " << password << endl;
}

void User::printAll()
{
    for (int i = 0; users[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        users[i]->print();
        cout << endl;
    }
}

bool User::checkAuth(string un, string pa)
{
    if (username == un)
    {
        if (password == pa)
            return true;
    }
    return false;
}

bool User::checkPermTi(string ti)
{
    for (int i = 0; permissions[i] != NULL; i++)
    {
        if (permissions[i]->viewTitle() == ti)
        {
            return true;
        }
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
    static void logout();
    static User *whoami();
};

User *Auth::login(string username, string password)
{
    for (int i = 0; users[i] != NULL; i++)
    {
        if (users[i]->checkAuth(username, password))
        {
            auth = users[i];
            return users[i];
        }
    }
    return NULL;
}

void Auth::logout()
{
    auth = NULL;
}

User *Auth::whoami()
{
    return auth;
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

Tag *Gtags[100] = {NULL};
Tag *Tag::create(string ti)
{
    Tag *temp = new Tag(ti);
    int i = 0;
    for (; Gtags[i] != NULL; i++)
    {
        ;
    }
    Gtags[i] = temp;
    return temp;
}

string Tag::veiwTitle()
{
    return title;
}

void Tag::print()
{
    cout << title;
}

void Tag::printAll()
{
    cout << "tags: \n";
    for (int i = 0; Gtags[i] != NULL; i++)
    {
        cout << "ID: " << i << '=';
        Gtags[i]->print();
        cout << endl;
    }
    cout << endl;
}

class Question
{
public:
    Question(string Qu, string ty, DateTime ti, User us) : question(Qu), type(ty), createdAt(ti), user(us) {}
    void publish() { isPublished = true; }
    void unpublish() { isPublished = false; }
    virtual void print() = 0;
    virtual void printAll() = 0;
    virtual Question *edit(string, DateTime, User, string, string, string, string, char) = 0;
    virtual Question *edit(string, DateTime, User) = 0;
    void addTag(Tag *);
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
        if (tags[i]->veiwTitle() == tag->veiwTitle())
            break;
    }
    if (tags[i] == NULL)
        tags[i] = tag;
}

string Question::TypeBack()
{
    return type;
}

Question *questions[100] = {NULL};

class FourChoice : public Question
{
public:
    FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans);
    void print();
    void printAll();
    Question *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) override;
    Question *edit(string, DateTime, User);
    static FourChoice *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

FourChoice::FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans) : Question(Qu, "four-choice", ti, us), A(a), B(b), C(c), D(d), answer(ans) {}

void FourChoice::print()
{
    cout << "Question: " << question << endl
         << "A) " << A << endl
         << "B) " << B << endl
         << "C) " << C << endl
         << "D) " << D << endl;
    cout << "Created at: " << createdAt.year << '/' << createdAt.month << '/' << createdAt.day
         << ' ' << createdAt.hour << ':' << createdAt.minute << ':' << createdAt.second << endl
         << "by user: ";
    user.print();
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
    if (isPublished)
        cout << "This question is published\n";
    else
        cout << "This question is not published\n";
}

void FourChoice::printAll()
{
    for (int i = 0; questions[i] != NULL; i++)
    {
        if (questions[i]->TypeBack() == "four-choice")
        {
            cout << "ID : " << i << endl;
            questions[i]->print();
        }
    }
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
        return new FourChoice(question, createdAt, user, A, B, C, D, answer);
    }
    else
    {
        cout << "You don't have the \"edit-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
}

FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    if (Auth::whoami()->checkPermTi("add-four-choice-question"))
    {
        FourChoice *x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        int i = 0;
        for (; questions[i] != NULL; i++)
        {
            ;
        }
        questions[i] = x;
        x->publish();
        return x;
    }
    else
    {
        cout << "You don't have the \"add-four-choice-question\" permission\n";
        return NULL;
    }
    return NULL;
}

class Descriptive : public Question
{
public:
    Descriptive(string qu, DateTime cr, User us);
    void AddAnswer(string ans);
    void print();
    void printAll();
    static Descriptive *create(string question, DateTime createdAt, User user);
    Question *edit(string, DateTime, User, string, string, string, string, char);
    Question *edit(string question, DateTime createdAt, User user) override;

private:
    string answer;
};

Descriptive::Descriptive(string qu, DateTime cr, User us) : Question(qu, "descriptive", cr, us) {}

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
         << "by user: ";
    user.print();
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        tags[i]->print();
        cout << ',';
    }
    cout << endl;
    if (isPublished)
        cout << "This question is published\n";
    else
        cout << "This question is not published\n";
}

void Descriptive::printAll()
{
    for (int i = 0; questions[i] != NULL; i++)
    {
        if (questions[i]->TypeBack() == "descriptive")
        {
            cout << "ID : " << i << endl;
            questions[i]->print();
        }
    }
}

Descriptive *Descriptive::create(string question, DateTime createdAt, User user)
{
    if (Auth::whoami()->checkPermTi("add-descriptive-question"))
    {
        Descriptive *x = new Descriptive(question, createdAt, user);
        int i = 0;
        for (; questions[i] != NULL; i++)
        {
            ;
        }
        questions[i] = x;
        x->publish();
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
        return new Descriptive(question, createdAt, user);
    }
    else
    {
        cout << "You don't have the \"edit-descriptive-question\" permission\n";
        return NULL;
    }
    return NULL;
}

void printDQ();
void printFQ();
void printAllQ();
void loginTMenu();
void loginFMenu();
void questionMenu();
void tagMenu();
void userMenu();

int main()
{
    users[0] = new User("admin", "admin", "123456");
    for (int i = 0; Gpermissions[i] != NULL; i++)
    {
        users[0]->addpermission(Gpermissions[i]);
    }
    if (Auth::whoami())
        loginTMenu();
    else
        loginFMenu();
    for (int i = 0; Gpermissions[i] != NULL; i++)
        delete Gpermissions[i];
    for (int i = 0; Gtags[i] != NULL; i++)
        delete Gtags[i];
    for (int i = 0; users[i] != NULL; i++)
        delete users[i];
    return 0;
}

void loginFMenu()
{
    char choice;
    while (true)
    {
        cout << "* Login(L)\n"
             << "* view All Questions(V)\n"
             << "* Exit(X)\n";

        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 'l':
        case 'L':
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
            break;
        }
        case 'v':
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
        {
            system("clear");
            break;
        }
    }
}

void loginTMenu()
{
    cout << "----------------------------------\n"
         << "Hello " << Auth::whoami()->myName() << "!\n"
         << "----------------------------------\n";

    char choice;
    while (true)
    {
        cout << "\t* Question Menu(Q)\n"
             << "\t* Tag Menu(T)\n"
             << "\t* User Menu(U)\n"
             << "\t* view All Questions(V)\n"
             << "\t* Exit(X)\n";
        cin >> choice;
        switch (choice)
        {
        case 'Q':
        case 'q':
            questionMenu();
            break;
        case 't':
        case 'T':
            tagMenu();
            break;
        case 'u':
        case 'U':
            userMenu();
            break;
        case 'v':
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
        {
            system("clear");
            break;
        }
    }
}

void questionMenu()
{
    char choice;
    while (true)
    {
        cout << "Question Menu\n";
        cout << "\t* Create Descriptive Question(C)\n"
             << "\t* Edit Descriptive Question(E)\n"
             << "\t* List of Descriptive Questions with ID(D)\n"
             << "\t* Print Descriptive Question(P)\n"
             << "\t* Create FourChoice Question(U)\n"
             << "\t* Edit FourChoice Question(H)\n"
             << "\t* List of FourChoice Questions with ID(F)\n"
             << "\t* Print FourChoice Question(K)\n"
             << "\t* view All Questions(V)\n"
             << "\t* Exit(X)\n";
        cin >> choice;
        switch (choice)
        {
        case 'c':
        case 'C':
        {
            cin.ignore();
            string question;
            cout << "Enter the Question: \n";
            getline(cin, question);
            DateTime temp;
            cout << "\nEnter time of Creation in this format Y/M/D H:M:S: \n";
            cin >> temp.year >> temp.month >> temp.day >> temp.hour >> temp.minute >> temp.second;
            Descriptive::create(question, temp, *Auth::whoami());
            break;
        }
        case 'e':
        case 'E':
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
            break;
        }
        case 'd':
        case 'D':
        {
            printDQ();
            break;
        }
        case 'p':
        case 'P':
        {
            int ID;
            cout << " Enter the ID of the Question you want to print: \n";
            cin >> ID;
            questions[ID]->print();
            break;
        }
        case 'u':
        case 'U':
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
            break;
        }
        case 'h':
        case 'H':
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
            break;
        }
        case 'f':
        case 'F':
            printFQ();
            break;
        case 'k':
        case 'K':
        {
            int ID;
            cout << " Enter the ID of the Question you want to print: \n";
            cin >> ID;
            questions[ID]->print();
            break;
            break;
        }
        case 'v':
        case 'V':
            printAllQ();
            break;
        }
        if (choice == 'x' || choice == 'X')
        {
            system("clear");
            break;
        }
    }
}

void tagMenu()
{
    char choice;
    while (true)
    {
        cout << "Tag Menu\n";
        cout << "\t*List of Tags with ID(L)\n"
             << "\t*Create New Tag(T)\n"
             << "\t* Exit(X)\n";

        cin >> choice;
        switch (choice)
        {
        case 'l':
        case 'L':
            Tag::printAll();
            break;
        case 't':
        case 'T':
        {
            string temp;
            cout << "Enter the Tag you want to add: \n";
            cin.ignore();
            getline(cin, temp);
            Tag::create(temp);
            break;
        }
        }
        if (choice == 'x' || choice == 'X')
        {
            system("clear");
            break;
        }
    }
}

void userMenu()
{
    char choice;
    while (true)
    {
        cout << "User Menu\n";
        cout << "\t*List of Users with ID(L)\n"
             << "\t*Create New User(U)\n"
             << "\t*Add permission to a user(P)\n"
             << "\t* Exit(X)\n";

        cin >> choice;
        switch (choice)
        {
        case 'l':
        case 'L':
            User::printAll();
            break;
        case 'u':
        case 'U':
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
        case 'p':
        case 'P':
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
            break;
        }
        }
        if (choice == 'x' || choice == 'X')
        {
            system("clear");
            break;
        }
    }
}

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