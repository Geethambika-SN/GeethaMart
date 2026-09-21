#include <iostream>

#include "controller/ProductController.h"

int main()
{
    std::cout << "GeethaMart Backend is starting..."
              << std::endl;

    ProductController controller;

    // --------------------------------------------------
    // Test Product Creation
    // --------------------------------------------------

    Product product;

    product.sellerId = 5;
    product.name = "CRUD Test Laptop";
    product.description = "Product CRUD verification";
    product.priceCents = 50000;
    product.quantity = 10;
    product.category = "Electronics";

    std::cout << "\nTesting product creation..."
              << std::endl;

    if (!controller.createProduct(product))
    {
        std::cout << "Product creation failed."
                  << std::endl;

        return 1;
    }

    std::cout << "Product creation successful!"
              << std::endl;

    // --------------------------------------------------
    // Find the newly created product
    // --------------------------------------------------

    std::vector<Product> products =
        controller.getAllProducts();

    Product createdProduct;

    for (const Product &item : products)
    {
        if (item.name == "CRUD Test Laptop")
        {
            createdProduct = item;
            break;
        }
    }

    if (createdProduct.id == 0)
    {
        std::cout << "Could not find created product."
                  << std::endl;

        return 1;
    }

    std::cout << "\nCreated Product:"
              << std::endl;

    std::cout << "ID: "
              << createdProduct.id
              << " | Name: "
              << createdProduct.name
              << " | Price Cents: "
              << createdProduct.priceCents
              << " | Quantity: "
              << createdProduct.quantity
              << std::endl;

    // --------------------------------------------------
    // Test Product Update
    // --------------------------------------------------

    createdProduct.name = "Updated CRUD Laptop";
    createdProduct.priceCents = 75000;
    createdProduct.quantity = 20;

    std::cout << "\nTesting product update..."
              << std::endl;

    if (controller.updateProduct(createdProduct))
    {
        std::cout << "Product update successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "Product update failed."
                  << std::endl;

        return 1;
    }

    // --------------------------------------------------
    // Verify Update
    // --------------------------------------------------

    Product updatedProduct =
        controller.getProductById(createdProduct.id);

    std::cout << "\nUpdated Product:"
              << std::endl;

    std::cout << "ID: "
              << updatedProduct.id
              << " | Name: "
              << updatedProduct.name
              << " | Price Cents: "
              << updatedProduct.priceCents
              << " | Quantity: "
              << updatedProduct.quantity
              << std::endl;

    // --------------------------------------------------
    // Test Product Delete
    // --------------------------------------------------

    std::cout << "\nTesting product deletion..."
              << std::endl;

    if (controller.deleteProduct(createdProduct.id))
    {
        std::cout << "Product deletion successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "Product deletion failed."
                  << std::endl;

        return 1;
    }

    // --------------------------------------------------
    // Verify Delete
    // --------------------------------------------------

    Product deletedProduct =
        controller.getProductById(createdProduct.id);

    if (deletedProduct.id == 0)
    {
        std::cout << "Delete verification successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "ERROR: Product still exists!"
                  << std::endl;

        return 1;
    }

    return 0;
}