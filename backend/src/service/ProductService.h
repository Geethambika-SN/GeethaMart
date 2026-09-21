#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

#include "../model/Product.h"
#include "../repository/ProductRepository.h"

#include <vector>

class ProductService
{
private:
    ProductRepository repository;

public:
    bool addProduct(const Product &product);

    std::vector<Product> getAllProducts();

    Product getProductById(int id);

    bool updateProduct(const Product &product);

    bool deleteProduct(int id);
};

#endif