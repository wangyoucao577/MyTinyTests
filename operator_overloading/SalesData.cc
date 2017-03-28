
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
    int val = 0;
    in >> val;
    data.set_price(val);

    in >> val;
    data.set_quantity(val);
    return in;
}


SalesData operator + (const SalesData& first, const SalesData& second){
    SalesData d(0, 0);
    d.set_price(first.price() + second.price());
    d.set_quantity(first.quantity() + second.quantity());
    return d;
}

/*
SalesData& operator += (SalesData& first, const SalesData& second){
    first.set_price(first.price() + second.price());
    first.set_quantity(first.quantity() + second.quantity());
    return first;
}*/
