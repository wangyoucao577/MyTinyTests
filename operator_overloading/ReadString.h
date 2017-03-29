
#ifndef _READ_STRING_H_
#define _READ_STRING_H_

#include <iostream>
#include <string>

class ReadString{
public:
    ReadString(std::istream& in = std::cin) : in_(in) {}

    std::string operator()(){
        std::string s;
        in_ >> s;
        if (!in_){
            s = "";
        }
        return s;
    }

private:
    std::istream& in_;

};

#endif

