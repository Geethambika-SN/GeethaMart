#ifndef REVIEW_SERVICE_H
#define REVIEW_SERVICE_H

#include "../model/Review.h"
#include "../repository/ReviewRepository.h"

#include <vector>

class ReviewService
{
private:
    ReviewRepository repository;

public:
    bool addReview(
        const Review &review);

    std::vector<Review> getReviewsByProduct(
        int productId);

    std::vector<Review> getReviewsByUser(
        int userId);

    bool updateReview(
        const Review &review);

    bool deleteReview(
        int reviewId,
        int userId);
};

#endif