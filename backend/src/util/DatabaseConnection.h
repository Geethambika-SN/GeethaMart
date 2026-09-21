#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <libpq-fe.h>
#include <string>

class DatabaseConnection
{
private:
    PGconn* connection;

public:
    DatabaseConnection();
    ~DatabaseConnection();

    bool connect();
    void disconnect();
    PGconn* getConnection();
};

#endif