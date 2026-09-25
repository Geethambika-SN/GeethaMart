#include "controller/UserController.h"
#include "controller/ProductController.h"
#include "controller/ReviewController.h"

#include <iostream>
#include <vector>

int main()
{
    std::cout << "STEP 149 - Review and Rating Test"
              << std::endl;

    std::cout << "========================================"
              << std::endl;

    UserController userController;
    ProductController productController;
    ReviewController reviewController;

    // --------------------------------------------------
    // 1. Create temporary Buyer
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Creating temporary Buyer..."
              << std::endl;

    User temporaryBuyer;

    temporaryBuyer.name =
        "Review Test Buyer";

    temporaryBuyer.email =
        "reviewtest@geethamart.com";

    temporaryBuyer.password =
        "Geetha123";

    temporaryBuyer.role =
        "BUYER";

    if (!userController.registerUser(
            temporaryBuyer))
    {
        std::cout << "Temporary Buyer creation failed."
                  << std::endl;

        return 1;
    }

    // --------------------------------------------------
    // 2. Login as temporary Buyer
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Logging in as temporary Buyer..."
              << std::endl;

    User buyer =
        userController.loginUser(
            "reviewtest@geethamart.com",
            "Geetha123");

    if (buyer.id == 0 ||
        buyer.role != "BUYER")
    {
        std::cout << "Temporary Buyer login failed."
                  << std::endl;

        return 1;
    }

    std::cout << "Temporary Buyer login successful."
              << std::endl;

    std::cout << "Temporary Buyer ID: "
              << buyer.id
              << std::endl;

    // --------------------------------------------------
    // 3. Create temporary product
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Creating temporary product..."
              << std::endl;

    Product temporaryProduct;

    temporaryProduct.sellerId = 5;
    temporaryProduct.name =
        "Review Test Product";
    temporaryProduct.description =
        "Temporary product for Step 149.";
    temporaryProduct.priceCents = 1500;
    temporaryProduct.quantity = 10;
    temporaryProduct.category = "Test";

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
            "Review Test Product")
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
    // 4. Add review
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Adding review..."
              << std::endl;

    Review review;

    review.productId =
        temporaryProductId;

    review.userId =
        buyer.id;

    review.rating =
        5;

    review.comment =
        "Excellent product.";

    if (!reviewController.addReview(
            review))
    {
        std::cout << "Failed to add review."
                  << std::endl;

        return 1;
    }

    std::cout << "Review added successfully."
              << std::endl;

    // --------------------------------------------------
    // 5. Get reviews for product
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Getting reviews for product..."
              << std::endl;

    std::vector<Review> productReviews =
        reviewController.getReviewsByProduct(
            temporaryProductId);

    if (productReviews.empty())
    {
        std::cout << "No reviews found."
                  << std::endl;

        return 1;
    }

    int reviewId =
        productReviews.back().id;

    std::cout << "Review found."
              << std::endl;

    std::cout << "Review ID: "
              << reviewId
              << std::endl;

    std::cout << "Rating: "
              << productReviews.back().rating
              << std::endl;

    std::cout << "Comment: "
              << productReviews.back().comment
              << std::endl;

    // --------------------------------------------------
    // 6. Get reviews by user
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Getting reviews by Buyer..."
              << std::endl;

    std::vector<Review> userReviews =
        reviewController.getReviewsByUser(
            buyer.id);

    bool userReviewFound = false;

    for (const Review &userReview :
         userReviews)
    {
        if (userReview.id == reviewId)
        {
            userReviewFound = true;
            break;
        }
    }

    if (!userReviewFound)
    {
        std::cout << "User review was not found."
                  << std::endl;

        return 1;
    }

    std::cout << "User review found successfully."
              << std::endl;

    // --------------------------------------------------
    // 7. Update review
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Updating review..."
              << std::endl;

    Review updatedReview;

    updatedReview.id =
        reviewId;

    updatedReview.productId =
        temporaryProductId;

    updatedReview.userId =
        buyer.id;

    updatedReview.rating =
        4;

    updatedReview.comment =
        "Good product after testing.";

    if (!reviewController.updateReview(
            updatedReview))
    {
        std::cout << "Failed to update review."
                  << std::endl;

        return 1;
    }

    std::cout << "Review updated successfully."
              << std::endl;

    // --------------------------------------------------
    // 8. Verify updated review
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Verifying updated review..."
              << std::endl;

    std::vector<Review> updatedReviews =
        reviewController.getReviewsByProduct(
            temporaryProductId);

    bool updateCorrect = false;

    for (const Review &updated :
         updatedReviews)
    {
        if (updated.id == reviewId)
        {
            std::cout << "Updated rating: "
                      << updated.rating
                      << std::endl;

            std::cout << "Updated comment: "
                      << updated.comment
                      << std::endl;

            if (updated.rating == 4 &&
                updated.comment ==
                    "Good product after testing.")
            {
                updateCorrect = true;
            }

            break;
        }
    }

    if (!updateCorrect)
    {
        std::cout << "Review update verification failed."
                  << std::endl;

        return 1;
    }

    std::cout << "Review update verified."
              << std::endl;

    // --------------------------------------------------
    // 9. Test invalid rating
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Testing invalid rating..."
              << std::endl;

    Review invalidReview;

    invalidReview.productId =
        temporaryProductId;

    invalidReview.userId =
        buyer.id;

    invalidReview.rating =
        6;

    invalidReview.comment =
        "Invalid rating test.";

    if (reviewController.addReview(
            invalidReview))
    {
        std::cout << "STEP 149 FAILED: "
                  << "Invalid rating was accepted."
                  << std::endl;

        return 1;
    }

    std::cout << "Invalid rating correctly rejected."
              << std::endl;

    // --------------------------------------------------
    // 10. Test ownership protection
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Testing review ownership protection..."
              << std::endl;

    Review unauthorizedUpdate;

    unauthorizedUpdate.id =
        reviewId;

    unauthorizedUpdate.productId =
        temporaryProductId;

    unauthorizedUpdate.userId =
        5;

    unauthorizedUpdate.rating =
        1;

    unauthorizedUpdate.comment =
        "Unauthorized update.";

    if (reviewController.updateReview(
            unauthorizedUpdate))
    {
        std::cout << "STEP 149 FAILED: "
                  << "Unauthorized review update was accepted."
                  << std::endl;

        return 1;
    }

    std::cout << "Unauthorized update correctly rejected."
              << std::endl;

    if (reviewController.deleteReview(
            reviewId,
            5))
    {
        std::cout << "STEP 149 FAILED: "
                  << "Unauthorized review deletion was accepted."
                  << std::endl;

        return 1;
    }

    std::cout << "Unauthorized deletion correctly rejected."
              << std::endl;

    // --------------------------------------------------
    // 11. Delete review
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Deleting review..."
              << std::endl;

    if (!reviewController.deleteReview(
            reviewId,
            buyer.id))
    {
        std::cout << "Failed to delete review."
                  << std::endl;

        return 1;
    }

    std::cout << "Review deleted successfully."
              << std::endl;

    // --------------------------------------------------
    // 12. Verify deletion
    // --------------------------------------------------

    std::cout << std::endl;
    std::cout << "Verifying review deletion..."
              << std::endl;

    std::vector<Review> remainingReviews =
        reviewController.getReviewsByProduct(
            temporaryProductId);

    bool reviewStillExists = false;

    for (const Review &remaining :
         remainingReviews)
    {
        if (remaining.id == reviewId)
        {
            reviewStillExists = true;
            break;
        }
    }

    if (reviewStillExists)
    {
        std::cout << "STEP 149 FAILED: "
                  << "Review still exists after deletion."
                  << std::endl;

        return 1;
    }

    std::cout << "Review deletion verified."
              << std::endl;

    // --------------------------------------------------
    // 13. Final result
    // --------------------------------------------------

    std::cout << std::endl;

    std::cout << "STEP 149 PASSED: "
              << "Review and rating management works correctly."
              << std::endl;

    std::cout << std::endl;

    std::cout << "Temporary Buyer ID: "
              << buyer.id
              << std::endl;

    std::cout << "Temporary Product ID: "
              << temporaryProductId
              << std::endl;

    std::cout << std::endl;

    std::cout << "IMPORTANT: "
              << "Temporary Buyer and product must be cleaned "
              << "from PostgreSQL after the test."
              << std::endl;

    return 0;
}