#include "ReviewRepository.h"
#include "../util/DatabaseConnection.h"

#include <iostream>
#include <string>
#include <vector>
#include <libpq-fe.h>

bool ReviewRepository::addReview(
    const Review &review)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    std::string productIdString =
        std::to_string(review.productId);

    std::string userIdString =
        std::to_string(review.userId);

    std::string ratingString =
        std::to_string(review.rating);

    const char* values[4];

    values[0] = productIdString.c_str();
    values[1] = userIdString.c_str();
    values[2] = ratingString.c_str();
    values[3] = review.comment.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "INSERT INTO reviews "
        "(product_id, user_id, rating, comment) "
        "VALUES ($1, $2, $3, $4);",
        4,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "Failed to add review: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }

    PQclear(result);

    return true;
}

std::vector<Review>
ReviewRepository::getReviewsByProduct(
    int productId)
{
    std::vector<Review> reviews;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return reviews;
    }

    std::string productIdString =
        std::to_string(productId);

    const char* values[1];

    values[0] = productIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "SELECT id, product_id, user_id, "
        "rating, comment "
        "FROM reviews "
        "WHERE product_id = $1 "
        "ORDER BY id;",
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get product reviews: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return reviews;
    }

    int rowCount =
        PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        Review review;

        review.id =
            std::stoi(
                PQgetvalue(result, row, 0));

        review.productId =
            std::stoi(
                PQgetvalue(result, row, 1));

        review.userId =
            std::stoi(
                PQgetvalue(result, row, 2));

        review.rating =
            std::stoi(
                PQgetvalue(result, row, 3));

        review.comment =
            PQgetvalue(result, row, 4);

        reviews.push_back(review);
    }

    PQclear(result);

    return reviews;
}

std::vector<Review>
ReviewRepository::getReviewsByUser(
    int userId)
{
    std::vector<Review> reviews;

    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return reviews;
    }

    std::string userIdString =
        std::to_string(userId);

    const char* values[1];

    values[0] = userIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "SELECT id, product_id, user_id, "
        "rating, comment "
        "FROM reviews "
        "WHERE user_id = $1 "
        "ORDER BY id;",
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "Failed to get user reviews: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return reviews;
    }

    int rowCount =
        PQntuples(result);

    for (int row = 0; row < rowCount; ++row)
    {
        Review review;

        review.id =
            std::stoi(
                PQgetvalue(result, row, 0));

        review.productId =
            std::stoi(
                PQgetvalue(result, row, 1));

        review.userId =
            std::stoi(
                PQgetvalue(result, row, 2));

        review.rating =
            std::stoi(
                PQgetvalue(result, row, 3));

        review.comment =
            PQgetvalue(result, row, 4);

        reviews.push_back(review);
    }

    PQclear(result);

    return reviews;
}

bool ReviewRepository::updateReview(
    const Review &review)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    std::string reviewIdString =
        std::to_string(review.id);

    std::string ratingString =
        std::to_string(review.rating);

    const char* values[3];

    values[0] = ratingString.c_str();
    values[1] = review.comment.c_str();
    values[2] = reviewIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "UPDATE reviews "
        "SET rating = $1, comment = $2 "
        "WHERE id = $3;",
        3,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "Failed to update review: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }

    bool updated =
        std::stoi(
            PQcmdTuples(result)) > 0;

    PQclear(result);

    return updated;
}

bool ReviewRepository::deleteReview(
    int reviewId)
{
    DatabaseConnection database;

    if (!database.connect())
    {
        std::cerr << "Failed to connect to database."
                  << std::endl;
        return false;
    }

    std::string reviewIdString =
        std::to_string(reviewId);

    const char* values[1];

    values[0] = reviewIdString.c_str();

    PGresult* result = PQexecParams(
        database.getConnection(),
        "DELETE FROM reviews "
        "WHERE id = $1;",
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "Failed to delete review: "
                  << PQerrorMessage(
                         database.getConnection())
                  << std::endl;

        PQclear(result);
        return false;
    }

    bool deleted =
        std::stoi(
            PQcmdTuples(result)) > 0;

    PQclear(result);

    return deleted;
}