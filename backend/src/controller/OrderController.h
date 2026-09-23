#ifndef ORDER_CONTROLLER_H
#define ORDER_CONTROLLER_H

#include "../model/Order.h"
#include "../model/OrderItem.h"
#include "../service/OrderService.h"

#include <vector>

class OrderController
{
private:
    OrderService service;

public:
    bool checkout(int buyerId);

    std::vector<Order> getOrdersByBuyer(
        int buyerId);

    std::vector<OrderItem> getOrderItems(
        int orderId);

    std::vector<Order> getAllOrders();
};

#endif