
#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <iostream>
#include <vector>
#include <string>

class StrVec{
public:
    // 重载 operator= 以支持initializer_list赋值(不是初始化)
    StrVec& operator = (std::initializer_list<std::string>);

public:
    std::string ToString() const;

private:
    std::vector<std::string> vec_;
};

std::ostream& operator << (std::ostream& out, const StrVec& sv);

#endif

