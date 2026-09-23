#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "../model/User.h"
#include "../service/UserService.h"

#include <string>
#include <vector>

class UserController
{
private:
    UserService service;

public:
    bool registerUser(const User &user);

    User loginUser(
        const std::string &email,
        const std::string &password);

    std::vector<User> getAllUsers();

    bool deleteUser(int userId);
};

#endif