#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

#include "../model/Product.h"

#include <string>
#include <vector>

class ProductRepository
{
public:
bool addProduct(const Product &product);


std::vector<Product> getAllProducts();

std::vector<Product> getProductsBySeller(
    int sellerId);

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
