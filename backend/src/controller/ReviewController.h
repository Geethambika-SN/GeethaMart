#ifndef REVIEW_CONTROLLER_H
#define REVIEW_CONTROLLER_H

#include "../model/Review.h"
#include "../service/ReviewService.h"

#include <vector>

class ReviewController
{
private:
    ReviewService service;

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