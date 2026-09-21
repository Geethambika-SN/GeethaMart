#include "ProductRepository.h"
#include "../util/DatabaseConnection.h"
#include <iostream>
#include <string>
#include <vector>
#include <libpq-fe.h>

bool ProductRepository::addProduct(const Product& product, int sellerId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return false;
    }

    std::string query =
        "INSERT INTO products (seller_id, name, price_cents, stock_qty) "
        "VALUES ($1, $2, $3, $4);";

    std::string sellerIdString = std::to_string(sellerId);

    std::string priceCents =
        std::to_string(static_cast<long long>(product.price * 100));

    std::string quantity = std::to_string(product.quantity);

    const char* values[4];

    values[0] = sellerIdString.c_str();
    values[1] = product.name.c_str();
    values[2] = priceCents.c_str();
    values[3] = quantity.c_str();

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
        std::cout << "Product added successfully!" << std::endl;
        PQclear(result);
        return true;
    }
    else
    {
        std::cerr << "Failed to add product: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }
}

bool ProductRepository::sellerExists(int sellerId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return false;
    }

    std::string query =
        "SELECT id FROM users "
        "WHERE id = $1 AND role = 'SELLER';";

    std::string sellerIdString = std::to_string(sellerId);

    const char* values[1];
    values[0] = sellerIdString.c_str();

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
        std::cerr << "Failed to check seller: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }

    bool exists = PQntuples(result) > 0;

    PQclear(result);

    return exists;
}

std::vector<Product> ProductRepository::getAllProducts()
{
    std::vector<Product> products;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return products;
    }

    std::string query =
        "SELECT id, name, price_cents, stock_qty "
        "FROM products "
        "ORDER BY id;";

    PGresult* result = PQexec(
        database.getConnection(),
        query.c_str()
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to retrieve products: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);
        return products;
    }

    int rows = PQntuples(result);

    for (int i = 0; i < rows; i++)
    {
        Product product;

        product.id = std::stoi(PQgetvalue(result, i, 0));
        product.name = PQgetvalue(result, i, 1);

        double priceCents =
            std::stod(PQgetvalue(result, i, 2));

        product.price = priceCents / 100.0;

        product.quantity =
            std::stoi(PQgetvalue(result, i, 3));

        products.push_back(product);
    }

    PQclear(result);

    return products;
}

Product ProductRepository::getProductById(int productId)
{
    Product product;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return product;
    }

    std::string query =
        "SELECT id, name, price_cents, stock_qty "
        "FROM products "
        "WHERE id = $1;";

    std::string productIdString = std::to_string(productId);

    const char* values[1];
    values[0] = productIdString.c_str();

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
        std::cerr << "Failed to retrieve product: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);
        return product;
    }

    if (PQntuples(result) > 0)
    {
        product.id = std::stoi(PQgetvalue(result, 0, 0));
        product.name = PQgetvalue(result, 0, 1);

        double priceCents =
            std::stod(PQgetvalue(result, 0, 2));

        product.price = priceCents / 100.0;

        product.quantity =
            std::stoi(PQgetvalue(result, 0, 3));
    }

    PQclear(result);

    return product;
}

bool ProductRepository::updateProduct(
    int productId,
    const Product& product)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return false;
    }

    std::string query =
        "UPDATE products "
        "SET name = $1, price_cents = $2, stock_qty = $3 "
        "WHERE id = $4;";

    std::string priceCents =
        std::to_string(static_cast<long long>(product.price * 100));

    std::string quantity =
        std::to_string(product.quantity);

    std::string productIdString =
        std::to_string(productId);

    const char* values[4];

    values[0] = product.name.c_str();
    values[1] = priceCents.c_str();
    values[2] = quantity.c_str();
    values[3] = productIdString.c_str();

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
        bool updated = PQcmdTuples(result)[0] != '0';

        PQclear(result);

        if (updated)
        {
            std::cout << "Product updated successfully!"
                      << std::endl;
        }

        return updated;
    }

    std::cerr << "Failed to update product: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

bool ProductRepository::deleteProduct(int productId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database." << std::endl;
        return false;
    }

    std::string query =
        "DELETE FROM products "
        "WHERE id = $1;";

    std::string productIdString =
        std::to_string(productId);

    const char* values[1];
    values[0] = productIdString.c_str();

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

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        bool deleted = PQcmdTuples(result)[0] != '0';

        PQclear(result);

        if (deleted)
        {
            std::cout << "Product deleted successfully!"
                      << std::endl;
        }

        return deleted;
    }

    std::cerr << "Failed to delete product: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}