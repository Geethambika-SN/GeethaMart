#include "UserRepository.h"
#include "../util/DatabaseConnection.h"

#include <iostream>
#include <string>
#include <vector>
#include <libpq-fe.h>

bool UserRepository::registerUser(const User &user)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    std::string query =
        "INSERT INTO users "
        "(name, email, password_hash, role) "
        "VALUES ($1, $2, $3, $4);";

    const char* values[4];

    values[0] = user.name.c_str();
    values[1] = user.email.c_str();
    values[2] = user.passwordHash.c_str();
    values[3] = user.role.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        query.c_str(),
        4,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        std::cout << "User registered successfully!"
                  << std::endl;

        PQclear(result);
        return true;
    }

    std::cerr << "Failed to register user: "
              << PQerrorMessage(
                     database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

User UserRepository::findUserByEmail(
    const std::string &email)
{
    User user;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return user;
    }

    std::string query =
        "SELECT id, name, email, password_hash, role "
        "FROM users "
        "WHERE email = $1;";

    const char* values[1];

    values[0] = email.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        query.c_str(),
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to find user: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return user;
    }

    if (PQntuples(result) > 0)
    {
        user.id =
            std::stoi(PQgetvalue(result, 0, 0));

        user.name =
            PQgetvalue(result, 0, 1);

        user.email =
            PQgetvalue(result, 0, 2);

        user.passwordHash =
            PQgetvalue(result, 0, 3);

        user.role =
            PQgetvalue(result, 0, 4);
    }

    PQclear(result);

    return user;
}

std::vector<User> UserRepository::getAllUsers()
{
    std::vector<User> users;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return users;
    }

    std::string query =
        "SELECT id, name, email, role "
        "FROM users "
        "ORDER BY id;";

    PGresult* result = PQexec(
        database.getConnection(),
        query.c_str());

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get users: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return users;
    }

    int rowCount = PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        User user;

        user.id =
            std::stoi(PQgetvalue(result, row, 0));

        user.name =
            PQgetvalue(result, row, 1);

        user.email =
            PQgetvalue(result, row, 2);

        user.role =
            PQgetvalue(result, row, 3);

        users.push_back(user);
    }

    PQclear(result);

    return users;
}

bool UserRepository::deleteUser(int userId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    std::string query =
        "DELETE FROM users "
        "WHERE id = $1;";

    std::string userIdString =
        std::to_string(userId);

    const char* values[1];

    values[0] = userIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        query.c_str(),
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "Failed to delete user: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }

    bool deleted =
        std::string(PQcmdTuples(result)) == "1";

    PQclear(result);

    return deleted;
}