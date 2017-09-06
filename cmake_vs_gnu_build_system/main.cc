
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include "math_lib/math_lib.h"

#ifdef CMAKE_CONFIG_IN
#include "cmake_config.h"
#endif

using namespace std;

int power(int base, int exponent){
    cout << "called function: \'" << __func__ << "\' in file: " << __FILE__ << endl;

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
#if defined(DEBUG)
        cout << "DEBUG mode" << endl;
#endif
        cout << "Usage: " << endl;
        cout << "   my_pow <base> <exponent>" << endl;
        cout << "Sample: " << endl;
        cout << "   my_pow 10 2" << endl;
        return -1;
    }

    int base = atoi(argv[1]);
    int exponent = atoi(argv[2]);

    using pow_t = int(*)(int ,int);
    pow_t pow = power; 

#if defined(USE_MY_MATH_LIB)
    pow = power2;
#endif
    cout << "pow function type " << typeid(pow).name() << ", result " << pow(base, exponent) << endl;

    return 0;
}

