
#include <stdlib.h>

int power2(int base, int exponent){
        
    if (exponent == 0){ 
        return 1.0;
    }   
        
    int result = base;
    for (int i = 1; i < exponent; ++i){                                                                                                                                          
        result *= base;
    }   
    return result;
}       


