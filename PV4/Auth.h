#pragma once
#include "Users.h"

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
    User *temp = Gusers.give(0);
    for (int i = 1; temp != NULL; i++)
    {
        if (temp->checkAuth(username, password))
        {
            auth = temp;
            return temp;
        }
        temp = Gusers.give(i);
    }
    return NULL;
}