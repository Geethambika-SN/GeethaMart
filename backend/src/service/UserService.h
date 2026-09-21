#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../model/User.h"
#include "../repository/UserRepository.h"

class UserService
{
private:
    UserRepository repository;

public:
    bool registerUser(const User &user);

    User loginUser(
        const std::string &email,
        const std::string &password);
};

#endif