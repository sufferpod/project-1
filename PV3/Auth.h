#pragma once
#include "Users.h"

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

void Auth::logout()
{
    auth = NULL;
}

User *Auth::whoami()
{
    return auth;
}