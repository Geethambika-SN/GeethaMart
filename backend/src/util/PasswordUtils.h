#ifndef PASSWORD_UTILS_H
#define PASSWORD_UTILS_H

#include <string>

class PasswordUtils
{
public:
    static std::string hashPassword(
        const std::string &password);

    static bool verifyPassword(
        const std::string &password,
        const std::string &hash);
};

#endif