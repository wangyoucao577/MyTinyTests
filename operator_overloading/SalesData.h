
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

    // operator ++/-- overloading
    // NOTE: 以这个类的含义, 本不应该定义这两个操作符, 这里仅做示例, 懒得定义新类了
    // operator++/-- 前置
    // operator++/--(int) 后置
    SalesData& operator++();
    SalesData& operator--();
    SalesData operator++(int);
    SalesData operator--(int);

private:
    int price_ {0};
    int quantity_ {0};
};

std::ostream& operator << (std::ostream& out, const SalesData& data);
std::istream& operator >> (std::istream& in, SalesData& data);
SalesData operator + (const SalesData& first, const SalesData& second);
// operator += 应定义为类的成员函数更加合适, 因为改动了对象本身
//SalesData& operator += (SalesData& first, const SalesData& second);

bool operator == (const SalesData& first, const SalesData& second);
bool operator != (const SalesData& first, const SalesData& second);

#endif


