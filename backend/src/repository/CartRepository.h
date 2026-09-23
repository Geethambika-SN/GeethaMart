
#ifndef CART_REPOSITORY_H
#define CART_REPOSITORY_H

#include "../model/CartItem.h"

#include <vector>

class CartRepository
{
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

