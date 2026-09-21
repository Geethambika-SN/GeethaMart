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