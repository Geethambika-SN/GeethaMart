#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    int id = 0;
    std::string name = "";
    double price = 0.0;
    int quantity = 0;
};

#endif