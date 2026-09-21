#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    int id = 0;

    int sellerId = 0;

    std::string name = "";

    std::string description = "";

    // Store money as integer minor units (cents).
    long long priceCents = 0;

    int quantity = 0;

    std::string category = "";
};

#endif