
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>

class SalesData{

public:
    explicit SalesData(int p, int q): price_(p), quantity_(q) {}

public:
    int price() const { return price_; }
    int quantity() const { return quantity_; }

    void set_price(int p) { price_ = p; }
    void set_quantity(int q) { quantity_ = q; } 

public:  
    SalesData& operator += (const SalesData& second);

private:
    int price_ {0};
    int quantity_ {0};
};

std::ostream& operator << (std::ostream& out, const SalesData& data);
std::istream& operator >> (std::istream& in, SalesData& data);
SalesData operator + (const SalesData& first, const SalesData& second);
//SalesData& operator += (SalesData& first, const SalesData& second);

#endif


