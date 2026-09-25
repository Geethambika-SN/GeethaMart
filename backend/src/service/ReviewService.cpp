#include "ReviewService.h"

#include <iostream>
#include <algorithm>

bool ReviewService::addReview(
    const Review &review)
{
    if (review.productId <= 0 ||
        review.userId <= 0)
    {
        return false;
    }

    if (review.rating < 1 ||
        review.rating > 5)
    {
        return false;
    }

    return repository.addReview(review);
}

std::vector<Review>
ReviewService::getReviewsByProduct(
    int productId)
{
    if (productId <= 0)
    {
        return {};
    }

    return repository.getReviewsByProduct(
        productId);
}

std::vector<Review>
ReviewService::getReviewsByUser(
    int userId)
{
    if (userId <= 0)
    {
        return {};
    }

    return repository.getReviewsByUser(
        userId);
}

bool ReviewService::updateReview(
    const Review &review)
{
    if (review.id <= 0 ||
        review.userId <= 0)
    {
        return false;
    }

    if (review.rating < 1 ||
        review.rating > 5)
    {
        return false;
    }

    // Verify that the review belongs
    // to the user requesting the update.
    std::vector<Review> userReviews =
        repository.getReviewsByUser(
            review.userId);

    bool ownsReview = false;

    for (const Review &existingReview : userReviews)
    {
        if (existingReview.id == review.id)
        {
            ownsReview = true;
            break;
        }
    }

    if (!ownsReview)
    {
        return false;
    }

    return repository.updateReview(review);
}

bool ReviewService::deleteReview(
    int reviewId,
    int userId)
{
    if (reviewId <= 0 ||
        userId <= 0)
    {
        return false;
    }

    // Verify that the review belongs
    // to the user requesting the deletion.
    std::vector<Review> userReviews =
        repository.getReviewsByUser(
            userId);

    bool ownsReview = false;

    for (const Review &review : userReviews)
    {
        if (review.id == reviewId)
        {
            ownsReview = true;
            break;
        }
    }

    if (!ownsReview)
    {
        return false;
    }

    return repository.deleteReview(reviewId);
}