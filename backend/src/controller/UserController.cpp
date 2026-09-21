#include "UserController.h"

bool UserController::registerUser(const User &user)
{
    return service.registerUser(user);
}

User UserController::loginUser(
    const std::string &email,
    const std::string &password)
{
    return service.loginUser(email, password);
}