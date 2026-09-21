#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

#include "../model/Product.h"

#include <vector>

class ProductRepository
{
public:
    bool addProduct(const Product &product);

    std::vector<Product> getAllProducts();

    Product getProductById(int id);

    bool updateProduct(const Product &product);

    bool deleteProduct(int id);
};

#endif