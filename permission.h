#include <string>
#include <iostream>
using namespace std;

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