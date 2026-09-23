#include "OrderRepository.h"
#include "../util/DatabaseConnection.h"

#include <iostream>
#include <string>
#include <vector>
#include <libpq-fe.h>

bool OrderRepository::createOrder(
    const Order &order,
    const std::vector<OrderItem> &items)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    PGconn* connection =
        database.getConnection();

    PGresult* result =
        PQexec(connection, "BEGIN;");

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        PQclear(result);
        return false;
    }

    PQclear(result);

    std::string buyerIdString =
        std::to_string(order.buyerId);

    std::string totalString =
        std::to_string(order.totalAmountCents);

    const char* orderValues[3];

    orderValues[0] = buyerIdString.c_str();
    orderValues[1] = order.status.c_str();
    orderValues[2] = totalString.c_str();

    result = PQexecParams(
        connection,
        "INSERT INTO orders "
        "(buyer_id, status, total_amount_cents) "
        "VALUES ($1, $2, $3) "
        "RETURNING id;",
        3,
        nullptr,
        orderValues,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK ||
        PQntuples(result) == 0)
    {
        PQclear(result);
        PQexec(connection, "ROLLBACK;");
        return false;
    }

    int orderId =
        std::stoi(PQgetvalue(result, 0, 0));

    PQclear(result);

    for (const OrderItem &item : items)
    {
        std::string orderIdString =
            std::to_string(orderId);

        std::string productIdString =
            std::to_string(item.productId);

        std::string quantityString =
            std::to_string(item.quantity);

        std::string priceString =
            std::to_string(item.unitPriceCents);

        const char* itemValues[4];

        itemValues[0] = orderIdString.c_str();
        itemValues[1] = productIdString.c_str();
        itemValues[2] = quantityString.c_str();
        itemValues[3] = priceString.c_str();

        result = PQexecParams(
            connection,
            "INSERT INTO order_items "
            "(order_id, product_id, quantity, unit_price_cents) "
            "VALUES ($1, $2, $3, $4);",
            4,
            nullptr,
            itemValues,
            nullptr,
            nullptr,
            0
        );

        if (PQresultStatus(result) != PGRES_COMMAND_OK)
        {
            PQclear(result);
            PQexec(connection, "ROLLBACK;");
            return false;
        }

        PQclear(result);
    }

    result =
        PQexec(connection, "COMMIT;");

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        PQclear(result);
        return false;
    }

    PQclear(result);

    return true;
}

std::vector<Order> OrderRepository::getOrdersByBuyer(
    int buyerId)
{
    std::vector<Order> orders;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return orders;
    }

    std::string buyerIdString =
        std::to_string(buyerId);

    const char* values[1];

    values[0] = buyerIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "SELECT id, buyer_id, status, total_amount_cents "
        "FROM orders "
        "WHERE buyer_id = $1 "
        "ORDER BY id;",
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get buyer orders: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return orders;
    }

    int rowCount =
        PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        Order order;

        order.id =
            std::stoi(PQgetvalue(result, row, 0));

        order.buyerId =
            std::stoi(PQgetvalue(result, row, 1));

        order.status =
            PQgetvalue(result, row, 2);

        order.totalAmountCents =
            std::stoll(PQgetvalue(result, row, 3));

        orders.push_back(order);
    }

    PQclear(result);

    return orders;
}

std::vector<OrderItem> OrderRepository::getOrderItems(
    int orderId)
{
    std::vector<OrderItem> items;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return items;
    }

    std::string orderIdString =
        std::to_string(orderId);

    const char* values[1];

    values[0] = orderIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "SELECT id, order_id, product_id, "
        "quantity, unit_price_cents "
        "FROM order_items "
        "WHERE order_id = $1 "
        "ORDER BY id;",
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get order items: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return items;
    }

    int rowCount =
        PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        OrderItem item;

        item.id =
            std::stoi(PQgetvalue(result, row, 0));

        item.orderId =
            std::stoi(PQgetvalue(result, row, 1));

        item.productId =
            std::stoi(PQgetvalue(result, row, 2));

        item.quantity =
            std::stoi(PQgetvalue(result, row, 3));

        item.unitPriceCents =
            std::stoll(PQgetvalue(result, row, 4));

        items.push_back(item);
    }

    PQclear(result);

    return items;
}

std::vector<Order> OrderRepository::getAllOrders()
{
    std::vector<Order> orders;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return orders;
    }

    std::string query =
        "SELECT id, buyer_id, status, total_amount_cents "
        "FROM orders "
        "ORDER BY id;";

    PGresult* result = PQexec(
        database.getConnection(),
        query.c_str());

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get all orders: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return orders;
    }

    int rowCount =
        PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        Order order;

        order.id =
            std::stoi(PQgetvalue(result, row, 0));

        order.buyerId =
            std::stoi(PQgetvalue(result, row, 1));

        order.status =
            PQgetvalue(result, row, 2);

        order.totalAmountCents =
            std::stoll(PQgetvalue(result, row, 3));

        orders.push_back(order);
    }

    PQclear(result);

    return orders;
}