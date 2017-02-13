#pragma once

#include <initializer_list>
#include "comm_include.h"

enum Gender {boy, girl};

class ILPeople
{
public:
    ILPeople();
    ~ILPeople();

public:
    //以 initializer_list<T> 作为参数的构造函数, 以支持列表初始化
    ILPeople(initializer_list<pair<string, Gender>> l);

private:
    vector<pair<string, Gender>> data;
};

