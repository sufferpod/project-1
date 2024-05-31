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
    for (int i = 0; users[i] != NULL; i++)
    {
        if (users[i]->checkAuth(username, password))
        {
            auth = users[i];
            return users[i];
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
