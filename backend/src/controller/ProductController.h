#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include "../model/Product.h"
#include "../service/ProductService.h"
#include <vector>

class ProductController
{
private:
    ProductService service;

public:
    bool createProduct(const Product &product, int sellerId);

    std::vector<Product> getAllProducts();

    Product getProductById(int productId);

    bool updateProduct(int productId, const Product &product);

    bool deleteProduct(int productId);
};

#endif