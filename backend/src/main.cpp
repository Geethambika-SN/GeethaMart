
#include <iostream>
#include <vector>
#include <limits>

#include "controller/ProductController.h"

int main()
{
    std::cout << "GeethaMart Backend is starting..."
              << std::endl;

    ProductController controller;

    // --------------------------------------------------
    // Create test products
    // --------------------------------------------------

    Product laptop;

    laptop.sellerId = 5;
    laptop.name = "Search Test Laptop";
    laptop.description = "Powerful laptop for testing search";
    laptop.priceCents = 60000;
    laptop.quantity = 10;
    laptop.category = "Electronics";

    Product phone;

    phone.sellerId = 5;
    phone.name = "Search Test Phone";
    phone.description = "Smart mobile phone";
    phone.priceCents = 30000;
    phone.quantity = 15;
    phone.category = "Electronics";

    Product chair;

    chair.sellerId = 5;
    chair.name = "Search Test Chair";
    chair.description = "Comfortable office chair";
    chair.priceCents = 8000;
    chair.quantity = 20;
    chair.category = "Furniture";

    std::cout << "\nCreating test products..."
              << std::endl;

    bool laptopCreated =
        controller.createProduct(laptop);

    bool phoneCreated =
        controller.createProduct(phone);

    bool chairCreated =
        controller.createProduct(chair);

    if (laptopCreated &&
        phoneCreated &&
        chairCreated)
    {
        std::cout << "Test products created successfully!"
                  << std::endl;
    }
    else
    {
        std::cout << "Failed to create one or more test products."
                  << std::endl;

        return 1;
    }

    // --------------------------------------------------
    // Test Search
    // --------------------------------------------------

    std::cout << "\nTesting product search..."
              << std::endl;

    std::vector<Product> searchResults =
        controller.searchProducts("Laptop");

    std::cout << "Search results: "
              << searchResults.size()
              << std::endl;

    for (const Product &product : searchResults)
    {
        std::cout
            << "ID: " << product.id
            << " | Name: " << product.name
            << " | Price Cents: " << product.priceCents
            << " | Category: " << product.category
            << std::endl;
    }

    if (!searchResults.empty())
    {
        std::cout << "Product search successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "Product search failed!"
                  << std::endl;
    }

    // --------------------------------------------------
    // Test Filter
    // Electronics between 20,000 and 70,000 cents
    // --------------------------------------------------

    std::cout << "\nTesting product filter..."
              << std::endl;

    std::vector<Product> filterResults =
        controller.filterProducts(
            "Electronics",
            20000,
            70000);

    std::cout << "Filter results: "
              << filterResults.size()
              << std::endl;

    for (const Product &product : filterResults)
    {
        std::cout
            << "ID: " << product.id
            << " | Name: " << product.name
            << " | Price Cents: " << product.priceCents
            << " | Category: " << product.category
            << std::endl;
    }

    if (!filterResults.empty())
    {
        std::cout << "Product filter successful!"
                  << std::endl;
    }
    else
    {
        std::cout << "Product filter failed!"
                  << std::endl;
    }

    // --------------------------------------------------
    // Cleanup test products
    // --------------------------------------------------

    std::cout << "\nCleaning up test products..."
              << std::endl;

    std::vector<Product> allProducts =
        controller.getAllProducts();

    int deletedCount = 0;

    for (const Product &product : allProducts)
    {
        if (product.name == "Search Test Laptop" ||
            product.name == "Search Test Phone" ||
            product.name == "Search Test Chair")
        {
            if (controller.deleteProduct(product.id))
            {
                deletedCount++;
            }
        }
    }

    std::cout << "Test products deleted: "
              << deletedCount
              << std::endl;

    std::cout << "\nSearch and filter testing completed."
              << std::endl;

    return 0;
}

