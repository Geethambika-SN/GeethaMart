#include "OrderService.h"

#include "../repository/CartRepository.h"
#include "../repository/ProductRepository.h"

#include <iostream>
#include <vector>

bool OrderService::checkout(int buyerId)
{
    if (buyerId <= 0)
    {
        return false;
    }

    CartRepository cartRepository;
    ProductRepository productRepository;

    std::vector<CartItem> cart =
        cartRepository.getCart(buyerId);

    if (cart.empty())
    {
        return false;
    }

    Order order;

    order.buyerId = buyerId;
    order.status = "PENDING";
    order.totalAmountCents = 0;

    std::vector<OrderItem> orderItems;

    for (const CartItem &cartItem : cart)
    {
        if (cartItem.productId <= 0 ||
            cartItem.quantity <= 0)
        {
            return false;
        }

        Product product =
            productRepository.getProductById(
                cartItem.productId);

        if (product.id == 0)
        {
            return false;
        }

        if (cartItem.quantity > product.quantity)
        {
            return false;
        }

        OrderItem item;

        item.productId = product.id;
        item.quantity = cartItem.quantity;
        item.unitPriceCents = product.priceCents;

        order.totalAmountCents +=
            product.priceCents *
            cartItem.quantity;

        orderItems.push_back(item);
    }

    if (orderItems.empty())
    {
        return false;
    }

    bool orderCreated =
        repository.createOrder(
            order,
            orderItems);

    if (!orderCreated)
    {
        return false;
    }

    for (const OrderItem &item : orderItems)
    {
        Product product =
            productRepository.getProductById(
                item.productId);

        if (product.id == 0)
        {
            return false;
        }

        product.quantity -= item.quantity;

        if (!productRepository.updateProduct(product))
        {
            return false;
        }
    }

    if (!cartRepository.clearCart(buyerId))
    {
        return false;
    }

    return true;
}

std::vector<Order> OrderService::getOrdersByBuyer(
    int buyerId)
{
    if (buyerId <= 0)
    {
        return {};
    }

    return repository.getOrdersByBuyer(
        buyerId);
}

std::vector<OrderItem> OrderService::getOrderItems(
    int orderId)
{
    if (orderId <= 0)
    {
        return {};
    }

    return repository.getOrderItems(
        orderId);
}

std::vector<Order> OrderService::getAllOrders()
{
    return repository.getAllOrders();
}