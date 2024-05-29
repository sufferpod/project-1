using namespace std;
#include "permission.h"
class User
{
private:
    string name, username, password;
    Permission *permissions[100] = {NULL};

public:
    User(string n, string un, string pa) : name(n), username(un), password(pa) {}
    static User *create(string n, string un, string pa)
    {
        return new User(n, un, pa);
    }
};