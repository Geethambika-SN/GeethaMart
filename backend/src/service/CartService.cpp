
#include "CartService.h"

bool CartService::addToCart(const CartItem &item)
{
    if (item.userId <= 0)
    {
        return false;
    }

    if (item.productId <= 0)
    {
        return false;
    }

    if (item.quantity <= 0)
    {
        return false;
    }

    return repository.addToCart(item);
}

std::vector<CartItem> CartService::getCart(int userId)
{
    if (userId <= 0)
    {
        return {};
    }

    return repository.getCart(userId);
}

bool CartService::updateCartItem(
    int userId,
    int productId,
    int quantity)
{
    if (userId <= 0)
    {
        return false;
    }

    if (productId <= 0)
    {
        return false;
    }

    if (quantity <= 0)
    {
        return false;
    }

    return repository.updateCartItem(
        userId,
        productId,
        quantity);
}

bool CartService::removeFromCart(
    int userId,
    int productId)
{
    if (userId <= 0)
    {
        return false;
    }

    if (productId <= 0)
    {
        return false;
    }

    return repository.removeFromCart(
        userId,
        productId);
}

bool CartService::clearCart(int userId)
{
    if (userId <= 0)
    {
        return false;
    }

    return repository.clearCart(userId);
}

