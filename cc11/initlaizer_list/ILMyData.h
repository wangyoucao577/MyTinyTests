#pragma once

#include "comm_include.h"

class ILMyData
{
public:
    ILMyData();
    ~ILMyData();

public:
    ILMyData & operator [] (initializer_list<int> l);
    ILMyData & operator = (int v);

public:
    void Print();

private:
    vector<int> idx;    //辅助数组, 用于记录index
    vector<int> d;
};

