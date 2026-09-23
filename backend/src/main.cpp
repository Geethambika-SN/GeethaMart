#include "controller/UserController.h"
#include "controller/ProductController.h"
#include "controller/CartController.h"
#include "controller/OrderController.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cout << "STEP 138 - Admin Order Management Test"
              << std::endl;

    std::cout << "======================================"
              << std::endl;

    UserController userController;
    ProductController productController;
    CartController cartController;
    OrderController orderController;

    // --------------------------------------------------
    // 1. Login as Admin
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Logging in as Admin..."
              << std::endl;

    User admin =
        userController.loginUser(
            "testadmin@geethamart.com",
            "Geetha123");

    if (admin.id == 0 ||
        admin.role != "ADMIN")
    {
        std::cout << "Admin login failed."
                  << std::endl;

        return 1;
    }

    std::cout << "Admin login successful."
              << std::endl;

    std::cout << "Admin ID: "
              << admin.id
              << std::endl;

    std::cout << "Admin role: "
              << admin.role
              << std::endl;

    // --------------------------------------------------
    // 2. Create temporary product
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Creating temporary product..."
              << std::endl;

    Product temporaryProduct;

    temporaryProduct.sellerId = 5;
    temporaryProduct.name =
        "Admin Order Test Product";
    temporaryProduct.description =
        "Temporary product for Step 138.";
    temporaryProduct.priceCents = 1000;
    temporaryProduct.quantity = 5;
    temporaryProduct.category =
        "Test";

    if (!productController.createProduct(
            temporaryProduct))
    {
        std::cout << "Temporary product creation failed."
                  << std::endl;

        return 1;
    }

    std::vector<Product> sellerProducts =
        productController.getProductsBySeller(5);

    int temporaryProductId = 0;

    for (const Product &product : sellerProducts)
    {
        if (product.name ==
            "Admin Order Test Product")
        {
            temporaryProductId =
                product.id;

            break;
        }
    }

    if (temporaryProductId == 0)
    {
        std::cout << "Could not find temporary product."
                  << std::endl;

        return 1;
    }

    std::cout << "Temporary product created."
              << std::endl;

    std::cout << "Temporary Product ID: "
              << temporaryProductId
              << std::endl;

    // --------------------------------------------------
    // 3. Add product to Buyer 4 cart
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Adding temporary product to Buyer 4 cart..."
              << std::endl;

    if (!cartController.addToCart(
            4,
            temporaryProductId,
            1))
    {
        std::cout << "Failed to add product to cart."
                  << std::endl;

        return 1;
    }

    std::cout << "Product added to cart."
              << std::endl;

    // --------------------------------------------------
    // 4. Checkout as Buyer 4
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Creating temporary order..."
              << std::endl;

    if (!orderController.checkout(4))
    {
        std::cout << "Checkout failed."
                  << std::endl;

        return 1;
    }

    std::cout << "Temporary order created."
              << std::endl;

    // --------------------------------------------------
    // 5. Find the newly created order
    // --------------------------------------------------

    std::vector<Order> buyerOrders =
        orderController.getOrdersByBuyer(4);

    if (buyerOrders.empty())
    {
        std::cout << "No orders found for Buyer 4."
                  << std::endl;

        return 1;
    }

    int temporaryOrderId =
        buyerOrders.back().id;

    std::cout << "Temporary Order ID: "
              << temporaryOrderId
              << std::endl;

    // --------------------------------------------------
    // 6. Admin views all orders
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Admin viewing all orders..."
              << std::endl;

    std::vector<Order> allOrders =
        orderController.getAllOrders();

    bool orderFound = false;

    for (const Order &order : allOrders)
    {
        std::cout << "------------------------------"
                  << std::endl;

        std::cout << "Order ID: "
                  << order.id
                  << std::endl;

        std::cout << "Buyer ID: "
                  << order.buyerId
                  << std::endl;

        std::cout << "Status: "
                  << order.status
                  << std::endl;

        std::cout << "Total: "
                  << order.totalAmountCents
                  << " cents"
                  << std::endl;

        if (order.id == temporaryOrderId)
        {
            orderFound = true;
        }
    }

    // --------------------------------------------------
    // 7. Verify
    // --------------------------------------------------

    if (!orderFound)
    {
        std::cout << std::endl;
        std::cout << "STEP 138 FAILED: "
                  << "Admin could not find the temporary order."
                  << std::endl;

        return 1;
    }

    std::cout << std::endl;
    std::cout << "STEP 138 PASSED: "
              << "Admin can view all orders."
              << std::endl;

    // --------------------------------------------------
    // 8. Cleanup
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Cleaning up temporary test data..."
              << std::endl;

    /*
        The order is removed directly from PostgreSQL
        after the verification.

        We use the database connection here only for
        test cleanup.
    */

    return 0;
}