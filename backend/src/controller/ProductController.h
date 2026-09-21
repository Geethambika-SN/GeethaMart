
#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include "../model/Product.h"
#include "../service/ProductService.h"

#include <string>
#include <vector>

class ProductController
{
private:
    ProductService service;

public:
    bool createProduct(const Product &product);

    std::vector<Product> getAllProducts();

    Product getProductById(int id);

    bool updateProduct(const Product &product);

    bool deleteProduct(int id);

    std::vector<Product> searchProducts(
        const std::string &searchTerm);

    std::vector<Product> filterProducts(
        const std::string &category,
        long long minPriceCents,
        long long maxPriceCents);
};

#endif

