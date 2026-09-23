#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

#include "../model/Product.h"
#include "../repository/ProductRepository.h"

#include <string>
#include <vector>

class ProductService
{
private:
    ProductRepository repository;

public:
    bool addProduct(const Product &product);

    std::vector<Product> getAllProducts();

    std::vector<Product> getProductsBySeller(
        int sellerId);

    Product getProductById(int id);

    bool updateProduct(
        const Product &product,
        int sellerId);

    bool deleteProduct(
        int productId,
        int sellerId);

    std::vector<Product> searchProducts(
        const std::string &searchTerm);

    std::vector<Product> filterProducts(
        const std::string &category,
        long long minPriceCents,
        long long maxPriceCents);
};

#endif