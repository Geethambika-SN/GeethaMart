#include "ProductController.h"

bool ProductController::createProduct(
    const Product &product,
    int sellerId)
{
    return service.addProduct(product, sellerId);
}

std::vector<Product> ProductController::getAllProducts()
{
    return service.getAllProducts();
}

Product ProductController::getProductById(int productId)
{
    return service.getProductById(productId);
}

bool ProductController::updateProduct(
    int productId,
    const Product &product)
{
    return service.updateProduct(productId, product);
}

bool ProductController::deleteProduct(int productId)
{
    return service.deleteProduct(productId);
}