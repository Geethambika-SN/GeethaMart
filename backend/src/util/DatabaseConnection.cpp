#include "DatabaseConnection.h"
#include <iostream>

DatabaseConnection::DatabaseConnection()
    : connection(nullptr)
{
}

DatabaseConnection::~DatabaseConnection()
{
    disconnect();
}

bool DatabaseConnection::connect()
{
    connection = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=geethamart "
        "user=postgres "
        "password=Geetha123"
    );

    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cerr << "Database connection failed: "
                  << PQerrorMessage(connection);

        return false;
    }

    std::cout << "Database connected successfully!" << std::endl;
    return true;
}

void DatabaseConnection::disconnect()
{
    if (connection != nullptr)
    {
        PQfinish(connection);
        connection = nullptr;
    }
}

PGconn* DatabaseConnection::getConnection()
{
    return connection;
}