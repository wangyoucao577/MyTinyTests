
#include <stdlib.h>
#include <stdio.h>

int power2(int base, int exponent){
    printf("called function: \'%s\' in file: %s\n", __func__, __FILE__);  
    
    if (exponent == 0){ 
        return 1.0;
    }   
        
    int result = base;
    for (int i = 1; i < exponent; ++i){                                                                                                                                          
        result *= base;
    }   
    return result;
}       


