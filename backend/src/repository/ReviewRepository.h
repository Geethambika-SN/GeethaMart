#ifndef REVIEW_REPOSITORY_H
#define REVIEW_REPOSITORY_H

#include "../model/Review.h"

#include <vector>

class ReviewRepository
{
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
        int reviewId);
};

#endif