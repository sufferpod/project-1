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

Permission *Gpermissions[100] = {NULL};

Permission *Permission::create(string ti)
{
    Permission *x = new Permission(ti);
    int i = 0;
    for (; Gpermissions[i] != NULL; i++)
    {
        if (Gpermissions[i]->title == x->title)
            return NULL;
    }
    Gpermissions[i] = x;
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
        if (Gtags[i]->veiwTitle() == ti)
            return NULL;
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
        cout << "ID: " << i << endl;
        Gtags[i]->print();
    }
    cout << endl;
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

User *Gusers[100] = {NULL};

User *User::create(string n, string un, string pa, User *ami)
{
    if (ami->checkPermTi("add-user") && !ami->checkAuth(un, pa))
    {
        User *x = new User(n, un, pa);
        int i = 0;
        for (; Gusers[i] != NULL; i++)
        {
            ;
        }
        Gusers[i] = x;
        return x;
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
    for (int i = 0; Gusers[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        Gusers[i]->print();
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
    for (int i = 0; Gusers[i] != NULL; i++)
    {
        if (Gusers[i]->checkAuth(username, password))
        {
            auth = Gusers[i];
            return Gusers[i];
        }
    }
    return NULL;
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
    static void remove(int id);

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

Question *Gquestions[100] = {NULL};

void Question::remove(int id)
{
    for (; Gquestions[id + 1] != NULL; id++)
    {
        Gquestions[id] = Gquestions[id + 1];
    }
    Gquestions[id] = NULL;
}

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
        int i = 0;
        for (; Gquestions[i] != NULL; i++)
        {
            ;
        }
        x->publish();
        Gquestions[i] = x;
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
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        if (Gquestions[i]->TypeBack() == "descriptive")
        {
            if (Gquestions[i]->pubBack())
            {
                cout << "ID : " << i << endl;
                Gquestions[i]->print();
            }
            else
                cout << "ID: " << i << " Not published\n";
        }
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
        int i = 0;
        for (; Gquestions[i] != NULL; i++)
        {
            ;
        }
        x->publish();
        Gquestions[i] = x;
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
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        if (Gquestions[i]->TypeBack() == "four-choice")
        {
            if (Gquestions[i]->pubBack())
            {
                cout << "ID : " << i << endl;
                Gquestions[i]->print();
            }
            else
                cout << "ID: " << i << " Not published\n";
        }
    }
}

template <typename T>
void finalDelete(T *[]);
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
        cout << "\t* List of Tags with ID(1)\n"
             << "\t* Create New Tag(2)\n"
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
        cout << "\t* List of Users with ID(1)\n"
             << "\t* Create New User(2)\n"
             << "\t* Add permission to a user(3)\n"
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
}

void printAllQ()
{
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        cout << "ID: " << i << endl;
        if (Gquestions[i]->pubBack())
            Gquestions[i]->print();
        else
            cout << "Not published\n";
        cout << "---------------------------------\n";
    }
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
    Gquestions[ID]->edit(question, temp, *Auth::whoami());
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
    Gquestions[ID]->print();
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
    Gquestions[ID]->edit(question, temp, *Auth::whoami(), a, b, c, d, ans);
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
    Gquestions[ID]->print();
}

void addTagtoQuestion()
{
    int IDQ, IDT;
    cout << "Enter the ID of the Question you want to add to: \n";
    cin >> IDQ;
    cout << "Enter the ID of the Tag you want to add: \n";
    cin >> IDT;
    Gquestions[IDQ]->addTag(Gtags[IDT]);
}

void publishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Publish: \n";
    cin >> ID;
    Gquestions[ID]->publish();
}

void unPublishQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Unpublish: \n";
    cin >> ID;
    Gquestions[ID]->unpublish();
}

void deleteQuestion()
{
    int ID;
    cout << "Enter the ID of the Question you want to Delete: \n";
    cin >> ID;
    Question::remove(ID);
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
    Gusers[ID]->addpermission(Gpermissions[p - 1]);
}

void clear()
{
#ifdef __linux__
    system("clear");
#elif _WIN64
    system("cls");
#endif
}

template <typename T>
void finalDelete(T *globalArray[])
{
    for (int i = 0; globalArray[i] != NULL; i++)
        delete globalArray[i];
}

void loadUsers()
{
    Gusers[0] = new User("admin", "admin", "123456");
    for (int i = 0; Gpermissions[i] != NULL; i++)
    {
        Gusers[0]->addpermission(Gpermissions[i]);
    }
    Auth::login("admin", "123456");
    fstream Userfile("Users.txt", ios::in);
    string n, un, pa, permend;
    int u = 1;
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

        for (int i = 0; perms[i] != NULL; i++)
        {
            Gusers[u]->addpermission(perms[i]);
        }
        for (int i = 0; perms[i] != NULL; i++)
        {
            delete perms[i];
        }
        u++;
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
    for (int i = 1; Gusers[i] != NULL; i++)
    {
        Userfile << Gusers[i]->name << endl
                 << Gusers[i]->username << endl
                 << Gusers[i]->password << endl;
        for (int j = 0; Gusers[i]->permissions[i] != NULL; j++)
        {
            Userfile << Gusers[i]->permissions[j]->viewTitle() << endl;
        }
        Userfile << "permend";
        if (Gusers[i + 1] != NULL)
            Userfile << endl;
    }
    Userfile.close();
}

void unLoadQuestions()
{
    fstream Qfile("Questions.txt", ios::out | ios::trunc);
    for (int i = 0; Gquestions[i] != NULL; i++)
    {
        if (Gquestions[i]->TypeBack() == "descriptive")
        {
            Qfile << Gquestions[i]->TypeBack() << endl
                  << Gquestions[i]->isPublished << endl;
            Qfile << Gquestions[i]->question
                  << endl;
            Qfile << Gquestions[i]->createdAt.year << ' ' << Gquestions[i]->createdAt.month << ' '
                  << Gquestions[i]->createdAt.day << ' ' << Gquestions[i]->createdAt.hour << ' '
                  << Gquestions[i]->createdAt.minute << ' ' << Gquestions[i]->createdAt.second
                  << endl;
            Qfile << Gquestions[i]->user.name << endl
                  << Gquestions[i]->user.username << endl
                  << Gquestions[i]->user.password;
            if (Gquestions[i + 1] != NULL)
                Qfile << endl;
        }
        else
        {
            FourChoice *temp = dynamic_cast<FourChoice *>(Gquestions[i]);
            Qfile << Gquestions[i]->TypeBack() << endl
                  << Gquestions[i]->isPublished << endl;
            Qfile << Gquestions[i]->question
                  << endl;
            Qfile << Gquestions[i]->createdAt.year << ' ' << Gquestions[i]->createdAt.month << ' '
                  << Gquestions[i]->createdAt.day << ' ' << Gquestions[i]->createdAt.hour << ' '
                  << Gquestions[i]->createdAt.minute << ' ' << Gquestions[i]->createdAt.second
                  << endl;
            Qfile << Gquestions[i]->user.name << endl
                  << Gquestions[i]->user.username << endl
                  << Gquestions[i]->user.password << endl;
            Qfile << temp->A << endl
                  << temp->B << endl
                  << temp->C << endl
                  << temp->D << endl
                  << temp->answer;
            if (Gquestions[i + 1] != NULL)
                Qfile << endl;
        }
    }
    Qfile.close();
}

void finalGdelete()
{
    finalDelete<Permission>(Gpermissions);
    finalDelete<Tag>(Gtags);
    finalDelete<User>(Gusers);
    finalDelete<Question>(Gquestions);
}