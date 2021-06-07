
#include <iostream>

extern unsigned foo();
extern unsigned boo();

int main() {

    std::cout << std::hex 
        << '\n' << foo()
        << '\n' << boo()
        << std::endl;

    return 0;
}