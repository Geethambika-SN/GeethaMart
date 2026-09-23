
#ifndef CART_SERVICE_H
#define CART_SERVICE_H

#include "../model/CartItem.h"
#include "../repository/CartRepository.h"

#include <vector>

class CartService
{
private:
    CartRepository repository;

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

