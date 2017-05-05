
#include <stdlib.h>
#include <iostream>
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

    cout << power(base, exponent) << endl;

    return 0;
}

