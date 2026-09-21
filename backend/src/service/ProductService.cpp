#include "ProductService.h"

bool ProductService::addProduct(const Product &product)
{
    // Validate product name
    if (product.name.empty())
    {
        return false;
    }

    // Validate seller
    if (product.sellerId <= 0)
    {
        return false;
    }

    // Validate price
    if (product.priceCents <= 0)
    {
        return false;
    }

    // Validate stock quantity
    if (product.quantity < 0)
    {
        return false;
    }

    // Validate category
    if (product.category.empty())
    {
        return false;
    }

    return repository.addProduct(product);
}

std::vector<Product> ProductService::getAllProducts()
{
    return repository.getAllProducts();
}

Product ProductService::getProductById(int id)
{
    if (id <= 0)
    {
        return Product{};
    }

    return repository.getProductById(id);
}

bool ProductService::updateProduct(const Product &product)
{
    if (product.id <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.sellerId <= 0)
    {
        return false;
    }

    if (product.priceCents <= 0)
    {
        return false;
    }

    if (product.quantity < 0)
    {
        return false;
    }

    if (product.category.empty())
    {
        return false;
    }

    return repository.updateProduct(product);
}

bool ProductService::deleteProduct(int id)
{
    if (id <= 0)
    {
        return false;
    }

    return repository.deleteProduct(id);
}