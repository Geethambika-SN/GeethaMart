
#ifndef CART_CONTROLLER_H
#define CART_CONTROLLER_H

#include "../model/CartItem.h"
#include "../service/CartService.h"

#include <vector>

class CartController
{
private:
    CartService service;

public:
    bool addToCart(const CartItem &item);

    std::vector<CartItem> getCart(int userId);

    bool updateCartItem(
        int userId,
        int productId,
        int quantity);

    bool removeFromCart(
        int userId,
        int productId);

    bool clearCart(int userId);
};

#endif

