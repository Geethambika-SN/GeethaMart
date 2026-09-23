#include "ProductController.h"

bool ProductController::createProduct(
    const Product &product)
{
    return service.addProduct(product);
}

std::vector<Product> ProductController::getAllProducts()
{
    return service.getAllProducts();
}

std::vector<Product> ProductController::getProductsBySeller(
    int sellerId)
{
    return service.getProductsBySeller(sellerId);
}

Product ProductController::getProductById(int id)
{
    return service.getProductById(id);
}

bool ProductController::updateProduct(
    const Product &product,
    int sellerId)
{
    return service.updateProduct(
        product,
        sellerId);
}

bool ProductController::deleteProduct(
    int productId,
    int sellerId)
{
    return service.deleteProduct(
        productId,
        sellerId);
}

std::vector<Product> ProductController::searchProducts(
    const std::string &searchTerm)
{
    return service.searchProducts(searchTerm);
}

std::vector<Product> ProductController::filterProducts(
    const std::string &category,
    long long minPriceCents,
    long long maxPriceCents)
{
    return service.filterProducts(
        category,
        minPriceCents,
        maxPriceCents);
}