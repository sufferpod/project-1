#include <string>
#include "structs.h"
#include "Users.h"
#include "Tag.h"
using namespace std;
class Question
{
private:
public:
    Question(string Qu, string ty, User us, DateTime ti) : question(Qu), type(ty), createdAt(ti), user(us) {}
    void publish() { isPublished = true; }
    void unpublish() { isPublished = false; }
    virtual void print();
    virtual void printAll();
    void addTag(Tag *);

protected:
    string question;
    string type;
    DateTime createdAt;
    User user;
    bool isPublished = false;
};