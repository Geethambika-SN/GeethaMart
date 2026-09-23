#ifndef ORDER_SERVICE_H
#define ORDER_SERVICE_H

#include "../model/Order.h"
#include "../model/OrderItem.h"
#include "../repository/OrderRepository.h"

#include <vector>

class OrderService
{
private:
    OrderRepository repository;

public:
    bool checkout(
        int buyerId);

    std::vector<Order> getOrdersByBuyer(
        int buyerId);

    std::vector<OrderItem> getOrderItems(
        int orderId);

    std::vector<Order> getAllOrders();
};

#endif