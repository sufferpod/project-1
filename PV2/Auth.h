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
    for (int i = 0; Gusers.give(i) != NULL; i++)
    {
        if (Gusers.give(i)->checkAuth(username, password))
        {
            auth = Gusers.give(i);
            return Gusers.give(i);
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
