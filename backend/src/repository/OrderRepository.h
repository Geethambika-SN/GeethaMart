#ifndef ORDER_REPOSITORY_H
#define ORDER_REPOSITORY_H

#include "../model/Order.h"
#include "../model/OrderItem.h"

#include <vector>

class OrderRepository
{
public:
    bool createOrder(
        const Order &order,
        const std::vector<OrderItem> &items);

    std::vector<Order> getOrdersByBuyer(
        int buyerId);

    std::vector<OrderItem> getOrderItems(
        int orderId);

    std::vector<Order> getAllOrders();
};

#endif