#include "ReviewController.h"

bool ReviewController::addReview(
    const Review &review)
{
    return service.addReview(review);
}

std::vector<Review>
ReviewController::getReviewsByProduct(
    int productId)
{
    return service.getReviewsByProduct(
        productId);
}

std::vector<Review>
ReviewController::getReviewsByUser(
    int userId)
{
    return service.getReviewsByUser(
        userId);
}

bool ReviewController::updateReview(
    const Review &review)
{
    return service.updateReview(review);
}

bool ReviewController::deleteReview(
    int reviewId,
    int userId)
{
    return service.deleteReview(
        reviewId,
        userId);
}