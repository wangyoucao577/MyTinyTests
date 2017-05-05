
#include <stdlib.h>
#include <iostream>
#include "math_lib/math_lib.h"
#include "cmake_config.h"

using namespace std;

int power(int base, int exponent){

    if (exponent == 0){
        return 1.0;
    }
    
    int result = base;
    for (int i = 1; i < exponent; ++i){
        result *= base;
    }
    return result;
}

int main(int argc, char* argv[]){

    if (argc < 3){
        cout << "Usage: " << endl;
        cout << "   my_pow <base> <exponent>" << endl;
        cout << "Sample: " << endl;
        cout << "   my_pow 10 2" << endl;
        return -1;
    }

    int base = atoi(argv[1]);
    int exponent = atoi(argv[2]);

#if defined(USE_MY_MATH_LIB)
    cout << "USE_MY_MATH_LIB power2() "  << power2(base, exponent) << endl;
#else
    cout << "use power() " << power(base, exponent) << endl;
#endif

    return 0;
}

