#include "OrderController.h"

bool OrderController::checkout(int buyerId)
{
    return service.checkout(buyerId);
}

std::vector<Order> OrderController::getOrdersByBuyer(
    int buyerId)
{
    return service.getOrdersByBuyer(
        buyerId);
}

std::vector<OrderItem> OrderController::getOrderItems(
    int orderId)
{
    return service.getOrderItems(
        orderId);
}

std::vector<Order> OrderController::getAllOrders()
{
    return service.getAllOrders();
}