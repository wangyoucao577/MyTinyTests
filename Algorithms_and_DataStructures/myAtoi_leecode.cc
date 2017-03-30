#include <string>
#include <ctype.h>
#include <climits>
#include <iostream>
using namespace std;

class Solution {
public:
    int myAtoi(string str){
        if (str.empty()){
            return 0;
        } 
        
        int val = 0;
        int converted_char = 0;
        const int kMaxDecimalIntLength = 10;
        bool is_positive = true;
        bool start_convert = false;

        auto char2int = [](char c){
            int a = c - '0';
            return a;
        };
            
        for (auto it = str.begin(); it != str.end(); it++){
            char c = *it;
            if (start_convert){
                //finish convert if cross limit or meet no digit  
                if (isdigit(c)){
                    int tmp = char2int(c);
                    converted_char++;
                    if (converted_char >= kMaxDecimalIntLength){
                        // check whether over limit

                        bool overlimit = false;
                        if (converted_char > kMaxDecimalIntLength){
                            overlimit = true;
                        }else {
                            if (INT_MAX / 10 < val){
                                overlimit = true;
                            }else if (INT_MAX / 10 == val && (is_positive ? INT_MAX % 10 : -(INT_MIN % 10)) < tmp){
                                overlimit = true;
                            }
                        }
                        
                        if (overlimit){
                            val = is_positive ? INT_MAX : INT_MIN;
                            return val;
                        }
                    }
                    
                    val *= 10;  //Decimal
                    val += (tmp % 10);
                }else{  
                    //convert done while meet no digit
                    break;
                }  
            }else{
                //ignore as many spaces
                
                if (isspace(c)){
                    //ignore it
                }else if (c == '-'){    //ready for next convert
                    is_positive = false;
                    start_convert = true;
                }else if (c == '+'){    //ready for next convert
                    start_convert = true;
                }else if (isdigit(c)){
                    start_convert = true;

                    // convert this charactor first
                    val = char2int(c);
                    converted_char++;

                }else{
                    //incorrect input. exit
                    return 0;
                }

            }
        } 
        
        if (!is_positive){
            val = -val;
        }
        return val;
    }
};


int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "Usage: myatoi <str>" << endl;
        cout << "   Sample: myatoi 1000" << endl;
        return 0; 
    }

    string s(argv[1]);
    Solution ma;
    cout << ma.myAtoi(s) << endl;
    
    return 0;
}
