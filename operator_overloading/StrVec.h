
#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <iostream>
#include <vector>
#include <string>

class StrVec{
public:
    // 重载 operator= 以支持initializer_list赋值(不是初始化)
    StrVec& operator = (std::initializer_list<std::string>);
    
    // 重载 operator= 以支持拷贝赋值
    StrVec& operator= (const StrVec&);

    // 重载 operator[] 的常量与非常量版本
    // 以供const和非const的StrVec对象调用
    std::string& operator[](std::size_t n){
        return vec_[n];
    }
    const std::string& operator[](std::size_t n) const{
        return vec_[n];
    }

public:
    std::string ToString() const;

private:
    std::vector<std::string> vec_;
};

std::ostream& operator << (std::ostream& out, const StrVec& sv);

#endif

