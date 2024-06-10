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
    for (int i = 0; Gusers[i] != NULL; i++)
    {
        if (Gusers[i]->checkAuth(username, password))
        {
            auth = Gusers[i];
            return Gusers[i];
        }
    }
    return NULL;
}