#include <iostream>
#include <cstdlib>
using namespace std;

User *users[100] = {NULL};
User admin("admin", "admin", "123456");
Permission *permissions[100] = {new permission("add-descriptive-question"), new permission("add-four-choice-question"),
                                new permission("edit-descriptive-question"), new permission("edit-four-choice-question"),
                                new permission("add-user"), NULL};
Question *questions[100] = {NULL};
Tag *tags[100] = {NULL};

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
    static Permission *create(string ti)
    {
        return new Permission(ti);
    }
    void print()
    {
        cout << title << endl;
    }
    string viewTitle()
    {
        return title;
    }
};

class User
{
private:
    string name, username, password;
    Permission *permissions[100] = {NULL};

public:
    User(string n, string un, string pa) : name(n), username(un), password(pa) {}
    static User *create(string n, string un, string pa)
    {
        User *x = new User(n, un, pa);
        int i = 0;
        for (; users[i] != NULL; i++)
        {
            ;
        }
        users[i] = x;
        return x;
    }
    void addpermission(Permission *permission)
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
    void print()
    {
        cout << "Name: " << name
             << "\nUser name: " << username
             << "Password: " << password << endl;
    }
    bool checkAuth(string un, string pa)
    {
        if (username == un)
        {
            if (password == pa)
                return true;
        }
        return false;
    }
};

class Auth
{
private:
    static User *auth = NULL;

public:
    static User *login(string username, string password)
    {
        bool flag = 0;
        for (int i = 0; i < 100; i++)
        {
            if (users[i].chechAuth(username, password))
                flag = true;
        }
        if (flag)
        {
            User x = User("current", username, password);
            return x;
        }
        else
            return NULL;
    }
    static void logout()
    {
        auth = NULL;
    }
    static User *whoami()
    {
        return auth;
    }
};

class Tag
{
private:
    string title;

public:
    Tag(string ti) : title(ti) {}
    static Tag *create(string ti)
    {
        return new Tag(ti);
    }
};

class Question
{
private:
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
        ;
    }
    tags[i] = tag;
}

class FourChoice : public Question
{
public:
    void printAll();
    FourChoice(string Qu, DateTime ti, User us, string A, string B, string C, string D, char answer) : Question(Qu, "FourChoice", ti, us), A(A), B(B), C(C), D(D), answer(answer) {}
    void print()
    {

        cout << "A) " << A << endl
             << "B) " << B << endl
             << "C) " << C << endl
             << "D) " << D << endl;
    }
    FourChoice *edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);
    static FourChoice *create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer);

private:
    string A, B, C, D;
    char answer;
};

FourChoice *FourChoice::edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
    this->answer = answer;
    return new FourChoice(question, createdAt, user, A, B, C, D, answer);
}
static FourChoice *FourChoice::create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer)
{
    FourChoice x = new FourChoice(question, createdAt, user, A, B, C, D, answer);
    return x;
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
        Descriptive x(question, createdAt, user);
        return &x;
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