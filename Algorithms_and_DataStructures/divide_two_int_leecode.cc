
#include <iostream>
#include <climits>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1)){ 
            return INT_MAX;
        }  

        bool val_positive = true;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)){
            val_positive = false;
        }    
    
        long long int lldividend = llabs(dividend);
        long long int lldivisor = llabs(divisor);
        long long int val = 0;
        cout << lldividend << endl; 
        
        /* 二进制左右移位计算除法  */ 
        
        int left = 0;
        long long int lefted_divisor = lldivisor;
        while (     lldividend > lefted_divisor 
                &&  lldividend >= ((lefted_divisor << 1)))
        {
            lefted_divisor <<= 1;
            left += 1;
        }
        cout << left << ", " << lefted_divisor << endl;

        //二进制除
        do {
            if (lldividend >= lefted_divisor){
                val |= ((long long int)1 << left);
                lldividend -= lefted_divisor;
            }
            --left;
            lefted_divisor >>= 1; 
        }while(left >= 0);         
        /* 二进制左右移位计算除法  */ 
        
        if (!val_positive){
            val = -val;
        }else {  
            if (val > INT_MAX){
                val = INT_MAX;
            }
        }
        return val;
    }
};

int kDivideTestMap[][3] = {
    /* dividend   divisor   expect_result*/
    {10, 2, 5},
    {10, -2, -5},
    {-10, 2, -5},
    {-10, -2, 5},
    {100, 0, INT_MAX},
    {INT_MIN, 0, INT_MAX},
    {INT_MIN, 1, INT_MIN},
    {INT_MAX, 1, INT_MAX},
    {INT_MIN, INT_MAX, -1},
    {INT_MAX, INT_MIN, 0},
    {100, 9, 11},
    {-100, 9, -11},
    {INT_MIN, -1, INT_MAX}, //overflow, so output INT_MAX
    {INT_MAX, 2, INT_MAX / 2}
};

int main(int argc, char* argv[]){

    Solution sl;
    for (int i = 0; i < sizeof(kDivideTestMap) / sizeof(kDivideTestMap[0]); ++i){
        cout << "Test Case " << i << ": " << kDivideTestMap[i][0] << " " << kDivideTestMap[i][1] << " " << kDivideTestMap[i][2] << endl;
        
        int val = sl.divide(kDivideTestMap[i][0], kDivideTestMap[i][1]);
        if(!(val == kDivideTestMap[i][2])){
            cout << kDivideTestMap[i][0] << " " << kDivideTestMap[i][1] << " " << kDivideTestMap[i][2] << ", calculated " << val << endl;
            assert(false);
        }
    }
    
    cout << "All Test Cases have been passed." << endl;
    return 0;
}
