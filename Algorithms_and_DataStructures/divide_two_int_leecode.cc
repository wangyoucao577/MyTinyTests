
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
        
        /* 二进制左右移位计算除法  */ 
       
        while (lldividend >= lldivisor){ 
            long long int llv = lldivisor; 
            int offset = 0;

            while (lldividend >= (llv << 1)){
                llv <<= 1;
                offset += 1;
            }
            lldividend -= llv;
            val |= ((long long int)1 << offset);
        }

        /* 二进制左右移位计算除法  */ 
        
        if (!val_positive){
            val = -val;
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
