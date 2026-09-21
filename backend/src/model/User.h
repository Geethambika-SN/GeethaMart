#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    int id = 0;

    std::string name = "";

    std::string email = "";

    // Plain-text password is used only during registration/login.
    std::string password = "";

    // Stored password hash.
    std::string passwordHash = "";

    std::string role = "BUYER";
};

#endif