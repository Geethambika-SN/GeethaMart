#include <iostream>

#include "controller/UserController.h"

int main()
{
    std::cout << "GeethaMart Backend is starting..."
              << std::endl;

    UserController controller;

    // --------------------------------------------------
    // Test ADMIN Registration
    // --------------------------------------------------

    User admin;

    admin.name = "Test Admin";
    admin.email = "testadmin@geethamart.com";
    admin.password = "Admin@123";
    admin.role = "ADMIN";

    std::cout << "\nTesting ADMIN registration..."
              << std::endl;

    bool adminRegistered =
        controller.registerUser(admin);

    if (adminRegistered)
    {
        std::cout << "ADMIN registration successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "ADMIN already exists or registration failed."
                  << std::endl;
    }

    // --------------------------------------------------
    // Test ADMIN Login
    // --------------------------------------------------

    std::cout << "\nTesting ADMIN login..."
              << std::endl;

    User loggedInAdmin =
        controller.loginUser(
            "testadmin@geethamart.com",
            "Admin@123");

    if (loggedInAdmin.id != 0 &&
        loggedInAdmin.role == "ADMIN")
    {
        std::cout << "ADMIN login successful!"
                  << std::endl;

        std::cout << "ID: "
                  << loggedInAdmin.id
                  << " | Name: "
                  << loggedInAdmin.name
                  << " | Email: "
                  << loggedInAdmin.email
                  << " | Role: "
                  << loggedInAdmin.role
                  << std::endl;
    }
    else
    {
        std::cout << "ADMIN login failed."
                  << std::endl;
    }

    // --------------------------------------------------
    // Test ADMIN Wrong Password
    // --------------------------------------------------

    std::cout << "\nTesting ADMIN login with wrong password..."
              << std::endl;

    User wrongPasswordAdmin =
        controller.loginUser(
            "testadmin@geethamart.com",
            "WrongPassword123");

    if (wrongPasswordAdmin.id == 0)
    {
        std::cout << "ADMIN wrong password rejected successfully!"
                  << std::endl;
    }
    else
    {
        std::cout << "ERROR: ADMIN wrong password was accepted!"
                  << std::endl;
    }

    return 0;
}