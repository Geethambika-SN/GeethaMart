#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

#include "../model/Product.h"
#include <vector>

class ProductRepository
{
public:
    bool addProduct(const Product &product, int sellerId);
    bool sellerExists(int sellerId);

    std::vector<Product> getAllProducts();
    Product getProductById(int productId);

    bool updateProduct(int productId, const Product &product);

    bool deleteProduct(int productId);
};

#endif