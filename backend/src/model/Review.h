#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review
{
public:
    int id = 0;
    int productId = 0;
    int userId = 0;
    int rating = 0;
    std::string comment = "";
};

#endif