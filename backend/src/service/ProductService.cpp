#include "ProductService.h"

bool ProductService::addProduct(const Product &product, int sellerId)
{
    if (sellerId <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.price <= 0)
    {
        return false;
    }

    if (product.quantity < 0)
    {
        return false;
    }

    if (!repository.sellerExists(sellerId))
    {
        return false;
    }

    return repository.addProduct(product, sellerId);
}

std::vector<Product> ProductService::getAllProducts()
{
    return repository.getAllProducts();
}

Product ProductService::getProductById(int productId)
{
    if (productId <= 0)
    {
        return Product{};
    }

    return repository.getProductById(productId);
}

bool ProductService::updateProduct(
    int productId,
    const Product &product)
{
    if (productId <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.price <= 0)
    {
        return false;
    }

    if (product.quantity < 0)
    {
        return false;
    }

    return repository.updateProduct(productId, product);
}

bool ProductService::deleteProduct(int productId)
{
    if (productId <= 0)
    {
        return false;
    }

    return repository.deleteProduct(productId);
}