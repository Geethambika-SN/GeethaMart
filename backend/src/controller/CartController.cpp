
#include "CartController.h"

bool CartController::addToCart(
    const CartItem &item)
{
    return service.addToCart(item);
}

std::vector<CartItem> CartController::getCart(
    int userId)
{
    return service.getCart(userId);
}

bool CartController::updateCartItem(
    int userId,
    int productId,
    int quantity)
{
    return service.updateCartItem(
        userId,
        productId,
        quantity);
}

bool CartController::removeFromCart(
    int userId,
    int productId)
{
    return service.removeFromCart(
        userId,
        productId);
}

bool CartController::clearCart(int userId)
{
    return service.clearCart(userId);
}

