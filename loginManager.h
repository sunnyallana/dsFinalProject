#pragma once
#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "user.h"

class loginManager {
private:
    linkedList<user*> registeredUsers;
    user* findUser(const char* userName);
public:
    loginManager();
    ~loginManager();
    user* loginUser(const char* userName, const char* userPassword);
    void logoutUser(user* loggedInUser);
    user* registerUser(const char* userName, const char* userPassword);
};
#endif