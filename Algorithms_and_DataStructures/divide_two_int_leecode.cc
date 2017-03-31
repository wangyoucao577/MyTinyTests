
#include <iostream>
#include <climits>
#include <assert.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0){ 
            return INT_MAX;
        }   
        if (dividend == divisor){
            return 1;
        }  
        if (divisor == INT_MIN){
            return 0;
        }
        if (divisor == 1){
            return dividend;
        }else if (divisor == -1){
            return dividend == INT_MIN ? INT_MAX : -dividend;
        }
                                                                                                                                    
        bool val_positive = true;
        int val = 0;

        bool append_1 = false;
        if (dividend == INT_MIN){
            append_1 = true;
            dividend += 1;
        }
                 
        //convert to positive to calculate
        if ((dividend > 0 && divisor < 0)){
            val_positive = false;
            divisor = -divisor;
        }else if (dividend < 0 && divisor > 0){
            val_positive = false;
            dividend = -dividend;
        }else if (dividend < 0 && divisor < 0){
            dividend = -dividend;
            divisor = -divisor;
        }
        
        /* 二进制左右移位计算除法  */ 
        
        //先取得divisor的二进制位数
        int divisor_bits = 0;
        int tmp_divisor = divisor;
        while (tmp_divisor != 0){
            tmp_divisor >>= 1;
            divisor_bits += 1;
        }

        //把被除数左移到手算的开始除的位置
        int left = 0;
        int lefted_divisor = divisor;
        while (     dividend > lefted_divisor 
                &&  dividend > ((lefted_divisor << 1) & 0x7FFFFFFF)
                //已经忽略了符号位的影响, 故最多左移30bits
                &&  left + 1 + divisor_bits < (sizeof(int) * 8))
        {
            lefted_divisor <<= 1;
            left += 1;
        }

        //二进制除
        do {
            if (dividend >= lefted_divisor){
                val += 1 << left;
                dividend -= lefted_divisor;
            }
            --left;
            lefted_divisor >>= 1; 
        }while(left >= 0);         
        /* 二进制左右移位计算除法  */ 
        
        /* 加法判断接近除数
        while (dividend >= divisor){
            dividend -= divisor;
            val += 1;
        }  */ 
        
        if (!val_positive){
            val = -val;
        }  
         
        if (append_1 && dividend + 1 >= divisor){
            if (val_positive){
                if (val != INT_MAX){
                    val += 1;
                }
            }else {
                val += (-1);
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
