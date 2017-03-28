
#include "SalesData.h"
using namespace std;


SalesData& SalesData::operator += (const SalesData& second){ 
    this->price_ += second.price();
    this->quantity_ += second.quantity();
    return *this;
}

std::ostream& operator << (std::ostream& out, const SalesData& data)
{
    out << data.price() << "\t" << data.quantity();
    return out;
}


std::istream& operator >> (std::istream& in, SalesData& data){
    int val1, val2;
    in >> val1 >> val2;
    if (in){    //若输入失败, 则忽略
        data.set_price(val1);
        data.set_quantity(val2);
    }

    return in;
}


SalesData operator + (const SalesData& first, const SalesData& second){
    SalesData d = first;
    
    // 使用 operator += 来实现 operator + 的技巧
    // 因为若要定义 operator +, 一般都会定义 operator +=
    d += second;
    return d;
}

/*
SalesData& operator += (SalesData& first, const SalesData& second){
    first.set_price(first.price() + second.price());
    first.set_quantity(first.quantity() + second.quantity());
    return first;
}*/


bool operator == (const SalesData& first, const SalesData& second){
    if (first.price() == second.price()
        &&  first.quantity() == second.quantity()){
        return true;
    }
    return false;
}


bool operator != (const SalesData& first, const SalesData& second){
    return !operator==(first, second);

}
