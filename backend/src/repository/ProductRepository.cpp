#include "ProductRepository.h"
#include "../util/DatabaseConnection.h"

#include <iostream>
#include <libpq-fe.h>

bool ProductRepository::addProduct(const Product &product)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "INSERT INTO products "
        "(seller_id, name, description, price_cents, stock_qty, category) "
        "VALUES ($1, $2, $3, $4, $5, $6);";

    std::string sellerId = std::to_string(product.sellerId);
    std::string priceCents = std::to_string(product.priceCents);
    std::string quantity = std::to_string(product.quantity);

    const char *values[6] =
    {
        sellerId.c_str(),
        product.name.c_str(),
        product.description.c_str(),
        priceCents.c_str(),
        quantity.c_str(),
        product.category.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        6,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        PQclear(result);
        std::cout << "Product added successfully!"
                  << std::endl;
        return true;
    }

    std::cerr << "Failed to add product: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);
    return false;
}

std::vector<Product> ProductRepository::getAllProducts()
{
    std::vector<Product> products;

    DatabaseConnection database;

    if (!database.connect())
    {
        return products;
    }

    const char *query =
        "SELECT id, seller_id, name, description, "
        "price_cents, stock_qty, category "
        "FROM products "
        "ORDER BY id;";

    PGresult *result =
        PQexec(database.getConnection(), query);

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get products: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);
        return products;
    }

    for (int row = 0; row < PQntuples(result); ++row)
    {
        Product product;

        product.id =
            std::stoi(PQgetvalue(result, row, 0));

        product.sellerId =
            std::stoi(PQgetvalue(result, row, 1));

        product.name =
            PQgetvalue(result, row, 2);

        product.description =
            PQgetvalue(result, row, 3);

        product.priceCents =
            std::stoll(PQgetvalue(result, row, 4));

        product.quantity =
            std::stoi(PQgetvalue(result, row, 5));

        product.category =
            PQgetvalue(result, row, 6);

        products.push_back(product);
    }

    PQclear(result);

    return products;
}

Product ProductRepository::getProductById(int id)
{
    Product product;

    DatabaseConnection database;

    if (!database.connect())
    {
        return product;
    }

    const char *query =
        "SELECT id, seller_id, name, description, "
        "price_cents, stock_qty, category "
        "FROM products "
        "WHERE id = $1;";

    std::string idValue = std::to_string(id);

    const char *values[1] =
    {
        idValue.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        PQclear(result);
        return product;
    }

    if (PQntuples(result) > 0)
    {
        product.id =
            std::stoi(PQgetvalue(result, 0, 0));

        product.sellerId =
            std::stoi(PQgetvalue(result, 0, 1));

        product.name =
            PQgetvalue(result, 0, 2);

        product.description =
            PQgetvalue(result, 0, 3);

        product.priceCents =
            std::stoll(PQgetvalue(result, 0, 4));

        product.quantity =
            std::stoi(PQgetvalue(result, 0, 5));

        product.category =
            PQgetvalue(result, 0, 6);
    }

    PQclear(result);

    return product;
}

bool ProductRepository::updateProduct(const Product &product)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "UPDATE products "
        "SET name = $1, "
        "description = $2, "
        "price_cents = $3, "
        "stock_qty = $4, "
        "category = $5 "
        "WHERE id = $6;";

    std::string priceCents =
        std::to_string(product.priceCents);

    std::string quantity =
        std::to_string(product.quantity);

    std::string id =
        std::to_string(product.id);

    const char *values[6] =
    {
        product.name.c_str(),
        product.description.c_str(),
        priceCents.c_str(),
        quantity.c_str(),
        product.category.c_str(),
        id.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        6,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        bool updated =
            PQcmdTuples(result)[0] != '0';

        PQclear(result);
        return updated;
    }

    std::cerr << "Failed to update product: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);
    return false;
}

bool ProductRepository::deleteProduct(int id)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "DELETE FROM products "
        "WHERE id = $1;";

    std::string idValue =
        std::to_string(id);

    const char *values[1] =
    {
        idValue.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        bool deleted =
            PQcmdTuples(result)[0] != '0';

        PQclear(result);
        return deleted;
    }

    std::cerr << "Failed to delete product: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);
    return false;
}