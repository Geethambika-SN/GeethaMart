#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order
{
public:
int id = 0;
int buyerId = 0;
std::string status = "PENDING";
long long totalAmountCents = 0;
};

#endif
