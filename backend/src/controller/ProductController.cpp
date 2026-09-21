
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

Product ProductController::getProductById(int id)
{
    return service.getProductById(id);
}

bool ProductController::updateProduct(
    const Product &product)
{
    return service.updateProduct(product);
}

bool ProductController::deleteProduct(int id)
{
    return service.deleteProduct(id);
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

