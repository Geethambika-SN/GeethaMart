
#include "CartRepository.h"
#include "../util/DatabaseConnection.h"

#include <iostream>
#include <string>
#include <libpq-fe.h>

bool CartRepository::addToCart(const CartItem &item)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "INSERT INTO cart_items "
        "(user_id, product_id, quantity) "
        "VALUES ($1, $2, $3) "
        "ON CONFLICT (user_id, product_id) "
        "DO UPDATE SET quantity = cart_items.quantity + EXCLUDED.quantity;";

    std::string userId =
        std::to_string(item.userId);

    std::string productId =
        std::to_string(item.productId);

    std::string quantity =
        std::to_string(item.quantity);

    const char *values[3] =
    {
        userId.c_str(),
        productId.c_str(),
        quantity.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        3,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        PQclear(result);

        std::cout << "Product added to cart successfully!"
                  << std::endl;

        return true;
    }

    std::cerr << "Failed to add product to cart: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

std::vector<CartItem> CartRepository::getCart(int userId)
{
    std::vector<CartItem> cartItems;

    DatabaseConnection database;

    if (!database.connect())
    {
        return cartItems;
    }

    const char *query =
        "SELECT id, user_id, product_id, quantity "
        "FROM cart_items "
        "WHERE user_id = $1 "
        "ORDER BY id;";

    std::string userIdValue =
        std::to_string(userId);

    const char *values[1] =
    {
        userIdValue.c_str()
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
        std::cerr << "Failed to get cart: "
                  << PQerrorMessage(database.getConnection())
                  << std::endl;

        PQclear(result);

        return cartItems;
    }

    for (int row = 0; row < PQntuples(result); ++row)
    {
        CartItem item;

        item.id =
            std::stoi(PQgetvalue(result, row, 0));

        item.userId =
            std::stoi(PQgetvalue(result, row, 1));

        item.productId =
            std::stoi(PQgetvalue(result, row, 2));

        item.quantity =
            std::stoi(PQgetvalue(result, row, 3));

        cartItems.push_back(item);
    }

    PQclear(result);

    return cartItems;
}

bool CartRepository::updateCartItem(
    int userId,
    int productId,
    int quantity)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "UPDATE cart_items "
        "SET quantity = $1 "
        "WHERE user_id = $2 "
        "AND product_id = $3;";

    std::string quantityValue =
        std::to_string(quantity);

    std::string userIdValue =
        std::to_string(userId);

    std::string productIdValue =
        std::to_string(productId);

    const char *values[3] =
    {
        quantityValue.c_str(),
        userIdValue.c_str(),
        productIdValue.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        3,
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

    std::cerr << "Failed to update cart item: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

bool CartRepository::removeFromCart(
    int userId,
    int productId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "DELETE FROM cart_items "
        "WHERE user_id = $1 "
        "AND product_id = $2;";

    std::string userIdValue =
        std::to_string(userId);

    std::string productIdValue =
        std::to_string(productId);

    const char *values[2] =
    {
        userIdValue.c_str(),
        productIdValue.c_str()
    };

    PGresult *result = PQexecParams(
        database.getConnection(),
        query,
        2,
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

    std::cerr << "Failed to remove cart item: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

bool CartRepository::clearCart(int userId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        return false;
    }

    const char *query =
        "DELETE FROM cart_items "
        "WHERE user_id = $1;";

    std::string userIdValue =
        std::to_string(userId);

    const char *values[1] =
    {
        userIdValue.c_str()
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
        PQclear(result);

        return true;
    }

    std::cerr << "Failed to clear cart: "
              << PQerrorMessage(database.getConnection())
              << std::endl;

    PQclear(result);

    return false;
}

