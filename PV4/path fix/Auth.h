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
    Node<User> *temp = Gusers.returnHead();
    while (temp != NULL)
    {
        if (temp->data->checkAuth(username, password))
        {
            auth = temp->data;
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}