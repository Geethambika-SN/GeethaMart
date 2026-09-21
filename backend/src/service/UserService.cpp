#include "UserService.h"
#include "../util/PasswordUtils.h"

#include <cctype>
#include <string>

bool UserService::registerUser(const User &user)
{
    // Validate name
    if (user.name.empty())
    {
        return false;
    }

    // Validate email
    if (user.email.empty())
    {
        return false;
    }

    std::size_t atPosition =
        user.email.find('@');

    std::size_t dotPosition =
        user.email.find('.', atPosition);

    if (atPosition == std::string::npos ||
        dotPosition == std::string::npos ||
        atPosition == 0 ||
        dotPosition <= atPosition + 1 ||
        dotPosition == user.email.length() - 1)
    {
        return false;
    }

    // Validate password
    if (user.password.length() < 8)
    {
        return false;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;

    for (unsigned char character : user.password)
    {
        if (std::isupper(character))
        {
            hasUppercase = true;
        }

        if (std::islower(character))
        {
            hasLowercase = true;
        }

        if (std::isdigit(character))
        {
            hasDigit = true;
        }
    }

    if (!hasUppercase ||
        !hasLowercase ||
        !hasDigit)
    {
        return false;
    }

    // Validate role
    if (user.role != "BUYER" &&
        user.role != "SELLER" &&
        user.role != "ADMIN")
    {
        return false;
    }

    // Check whether email already exists
    User existingUser =
        repository.findUserByEmail(user.email);

    if (existingUser.id != 0)
    {
        return false;
    }

    User newUser = user;

    // Hash password before storing it
    newUser.passwordHash =
        PasswordUtils::hashPassword(user.password);

    // Never keep the plain-text password
    newUser.password.clear();

    return repository.registerUser(newUser);
}

User UserService::loginUser(
    const std::string &email,
    const std::string &password)
{
    if (email.empty() || password.empty())
    {
        return User{};
    }

    User user =
        repository.findUserByEmail(email);

    if (user.id == 0)
    {
        return User{};
    }

    if (!PasswordUtils::verifyPassword(
            password,
            user.passwordHash))
    {
        return User{};
    }

    return user;
}