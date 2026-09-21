#include <iostream>
#include <vector>

#include "model/Product.h"
#include "controller/ProductController.h"

int main()
{
    std::cout << "GeethaMart Backend is starting..." << std::endl;

    ProductController controller;

    // Create test product
    Product product;

    product.name = "Delete Test Product";
    product.price = 200.00;
    product.quantity = 10;

    int sellerId = 3;

    bool created = controller.createProduct(product, sellerId);

    if (!created)
    {
        std::cout << "Product creation failed!" << std::endl;
        return 1;
    }

    std::cout << "Product creation successful!" << std::endl;

    // Get the newly created product
    std::vector<Product> products = controller.getAllProducts();

    if (products.empty())
    {
        std::cout << "No products found!" << std::endl;
        return 1;
    }

    int productId = products.back().id;

    std::cout << "\nCreated Product:" << std::endl;

    Product createdProduct = controller.getProductById(productId);

    std::cout << "ID: " << createdProduct.id
              << " | Name: " << createdProduct.name
              << " | Price: " << createdProduct.price
              << " | Quantity: " << createdProduct.quantity
              << std::endl;

    // Delete product
    bool deleted = controller.deleteProduct(productId);

    if (deleted)
    {
        std::cout << "\nProduct deletion successful!" << std::endl;
    }
    else
    {
        std::cout << "\nProduct deletion failed!" << std::endl;
        return 1;
    }

    // Verify product was deleted
    Product deletedProduct = controller.getProductById(productId);

    if (deletedProduct.id == 0)
    {
        std::cout << "Delete verification successful!" << std::endl;
    }
    else
    {
        std::cout << "Delete verification failed!" << std::endl;
        return 1;
    }

    return 0;
}