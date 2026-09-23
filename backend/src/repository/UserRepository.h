#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../model/User.h"

#include <string>
#include <vector>

class UserRepository
{
public:
    bool registerUser(const User &user);

    User findUserByEmail(
        const std::string &email);

    std::vector<User> getAllUsers();

    bool deleteUser(int userId);
};

#endif