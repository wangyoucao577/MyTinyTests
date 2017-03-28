
#include "Strvec.h"
using namespace std;

StrVec& StrVec::operator = (initializer_list<string> il){
    this->vec_.clear();
    for (auto & i : il){
        this->vec_.push_back(i);
    }
    return *this;
}


string StrVec::ToString() const{
    string s{"{ "};
    for (auto & i : this->vec_){
        s += i;
        s += " ";
    }
    s += " }";
    return s;
}

std::ostream& operator << (std::ostream& out, const StrVec& sv){
    out << sv.ToString();
    return out;
}
