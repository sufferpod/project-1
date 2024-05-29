#include <string>
#include "structs.h"
#include "Users.h"
#include "Tag.h"
using namespace std;
class Question
{
private:
public:
    void stub(string) {}
    Question(string Qu, string ty, DateTime ti) : question(Qu), type(ty), createdAt(ti), user(us)
    {
        user = stub(whoami);
    }
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
    for (; Tags[i] != NULL; i++)
    {
        ;
    }
    tags[i] = tag;
}