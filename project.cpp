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
    static User *create(string n, string un, string pa);
    void addpermission(Permission *permission);
    void print();
    bool checkAuth(string un, string pa);
};
User *users[100] = {NULL};
User *User::create(string n, string un, string pa)
{
    User *x = new User(n, un, pa);
    bool flag = false;
    for (int i = 0; x->permissions[i] != NULL; i++)
    {
        if (x->permissions[i]->viewTitle() == "add-user")
        {
            flag = true;
        }
    }
    if (flag)
    {
        int i = 0;
        for (; users[i] != NULL; i++)
        {
            if (x->username == users[i]->username)
            {
                break;
            }
        }
        if (users[i] == NULL)
        {
            users[i] = x;
            return x;
        }
    }
    return NULL;
}

void User::addpermission(Permission *permission)
{
    int i = 0;
    for (; Gpermissions[i] != NULL; i++)
    {
        if (Gpermissions[i]->viewTitle() == permission->viewTitle())
        {
            break;
        }
    }
    if (Gpermissions[i] == NULL)
    {
        Gpermissions[i] = permission;
    }
}

void User::print()
{
    cout << "Name: " << name
         << "\nUser name: " << username
         << "Password: " << password << endl;
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
    bool flag = 0;
    for (int i = 0; i < 100; i++)
    {
        if (users[i]->checkAuth(username, password))
            flag = true;
    }
    if (flag)
    {
        User *x = new User("current", username, password);
        auth = x;
        return x;
    }
    else
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
    void printAll();
};

Tag *Tag::create(string ti)
{
    return new Tag(ti);
}

string Tag::veiwTitle()
{
    return title;
}

void Tag::print()
{
    cout << title << endl;
}

Tag *Gtags[100] = {NULL};

void Tag::printAll()
{
    cout << "tags: ";
    for (int i = 0; Gtags[i] != NULL; i++)
    {
        cout << Gtags[i]->title << ',';
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
    void addTag(Tag *);

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

Question *questions[100] = {NULL};

class FourChoice : public Question
{
public:
    FourChoice(string Qu, DateTime ti, User us, string a, string b, string c, string d, char ans);
    void print();
    void printAll();
    FourChoice *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);
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
         << "by user ";
    user.print();
    cout << "Tags: ";
    for (int i = 0; tags[i] != NULL; i++)
    {
        cout << tags[i] << ',';
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
        if (questions[i]->type == "four-choice")
        {
            questions[i]->print();
        }
    }
}

FourChoice *FourChoice::edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    bool flag = false;
    for (int i = 0; Auth::whoami()->permissions[i] = NULL; i++)
    {
        if (whoami()->permissions[i]->title == "edit-four-choice-question")
            flag = true;
    }
    if (flag)
    {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->answer = answer;
        return new FourChoice(question, createdAt, user, A, B, C, D, answer);
    }
    else
        return NULL;
}

FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    bool flag = false;
    for (int i = 0; Auth::whoami()->permissions[i] = NULL; i++)
    {
        if (whoami()->permissions[i]->title == "add-four-choice-question")
            flag = true;
    }
    if (flag)
    {
        FourChoice *x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        int i = 0;
        for (; questions[i] != NULL; i++)
        {
            ;
        }
        questions[i] = x;
        return x;
    }
    return NULL;
}

class Descriptive : public Question
{
public:
    Descriptive(string qu, DateTime cr, User us) : Question(qu, "Descriptive", cr, us) {}
    void AddAnswer() { this->answer = answer; }
    void print() {}
    void printAll() {}
    static Descriptive *create(string question, DateTime createdAt, User user)
    {
        Descriptive *x = new Descriptive(question, createdAt, user);
        return x;
    }
    Descriptive *edit(string question, DateTime createdAt, User user)
    {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        return new Descriptive(question, createdAt, user);
    }

private:
    string answer;
};

void stub();
void login();
bool stup();
void questionMenu();
void tagMenu();
void userMenu();

int main()
{
    User admin("admin", "admin", "123456");
    for (int i = 0; Gpermissions[i] != NULL; i++)
    {
        admin.addpermission(Gpermissions[i]);
    }
    char choice;
    while (true)
    {
        cout << "* Login(L)" << endl;
        cout << "* view the Questions(v)" << endl;

        cin >> choice;
        switch (choice)
        {
        case 'l':
        case 'L':
            if (stup())
                login();
            else
                stub();
            break;
        case 'v':
        case 'V':
            stub();
            break;
        }
        system("cls");
    }
    return 0;
}
void stub()
{
}
bool stup()
{
    return 1;
}
void login()
{
    cout << "----------------------------------" << endl
         << "Hello" << stup() << '!'
         << "----------------------------------" << endl;
    char choice;

    while (true)
    {
        cout << "* Question menu(Q)" << endl;
        cout << "* Tag menu(T)" << endl;
        cout << "* User menu(U)" << endl;
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
        }
        system("cls");
    }
}
void questionMenu() {}
void tagMenu() {}
void userMenu() {}