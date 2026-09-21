#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../model/User.h"

class UserRepository
{
public:
    bool registerUser(const User &user);

    User findUserByEmail(const std::string &email);
};

#endif