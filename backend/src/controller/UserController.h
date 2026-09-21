#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "../model/User.h"
#include "../service/UserService.h"

class UserController
{
private:
    UserService service;

public:
    bool registerUser(const User &user);

    User loginUser(
        const std::string &email,
        const std::string &password);
};

#endif