#include <string>
#include"structs.h"
#include"Users.h"
#include"Tag.h"
using namespace std;
class Question
{
private:
public:
Question(User us, DateTime ti, string Qu): question(Qu), createdAt(ti), user(us){}
void publish(){isPublished = true;}
void unpublish(){isPublished = false;}
virtual void print();
virtual void printAll();
void addTag(Tag*);
protected:
    string question;
    DateTime createdAt;
    User user;
    bool isPublished = false;
};
#comment