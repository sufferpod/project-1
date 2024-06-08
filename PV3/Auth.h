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
    int i = 0;
    for (User *temp = Gusers.give(i); temp != NULL; i++)
    {
        if (temp->checkAuth(username, password))
        {
            auth = temp;
            return temp;
        }
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