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

std::vector<Product> ProductService::getProductsBySeller(
    int sellerId)
{
    if (sellerId <= 0)
    {
        return {};
    }

    return repository.getProductsBySeller(sellerId);
}

Product ProductService::getProductById(int id)
{
    if (id <= 0)
    {
        return Product{};
    }

    return repository.getProductById(id);
}

bool ProductService::updateProduct(
    const Product &product,
    int sellerId)
{
    // Validate seller identity
    if (sellerId <= 0)
    {
        return false;
    }

    // Validate product ID
    if (product.id <= 0)
    {
        return false;
    }

    // Check that the product exists
    Product existingProduct =
        repository.getProductById(product.id);

    if (existingProduct.id == 0)
    {
        return false;
    }

    // Ownership check
    if (existingProduct.sellerId != sellerId)
    {
        return false;
    }

    // Validate product name
    if (product.name.empty())
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

    // Use the authenticated seller ID
    Product updatedProduct = product;
    updatedProduct.sellerId = sellerId;

    return repository.updateProduct(updatedProduct);
}

bool ProductService::deleteProduct(
    int productId,
    int sellerId)
{
    // Validate seller identity
    if (sellerId <= 0)
    {
        return false;
    }

    // Validate product ID
    if (productId <= 0)
    {
        return false;
    }

    // Check that the product exists
    Product existingProduct =
        repository.getProductById(productId);

    if (existingProduct.id == 0)
    {
        return false;
    }

    // Ownership check
    if (existingProduct.sellerId != sellerId)
    {
        return false;
    }

    return repository.deleteProduct(productId);
}

std::vector<Product> ProductService::searchProducts(
    const std::string &searchTerm)
{
    // Search term must not be empty
    if (searchTerm.empty())
    {
        return {};
    }

    return repository.searchProducts(searchTerm);
}

std::vector<Product> ProductService::filterProducts(
    const std::string &category,
    long long minPriceCents,
    long long maxPriceCents)
{
    // Price range validation
    if (minPriceCents < 0)
    {
        return {};
    }

    if (maxPriceCents < minPriceCents)
    {
        return {};
    }

    // Category must not be empty
    if (category.empty())
    {
        return {};
    }

    return repository.filterProducts(
        category,
        minPriceCents,
        maxPriceCents);
}