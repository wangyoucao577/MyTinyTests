
#ifndef _PRINT_STRING_H_
#define _PRINT_STRING_H_

#include <iostream>
#include <string>

class PrintString{
public:
    PrintString(std::ostream& out = std::cout, char c = ' ') : out_(out), sep_(c){}

    void operator()(const std::string& s) const{ out_ << s << sep_; }

private:
    std::ostream& out_;
    char sep_;

};

#endif


