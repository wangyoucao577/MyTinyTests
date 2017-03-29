
#include <iostream>
#include <map>
#include <functional>
#include <string>
using namespace std;

int add(int i, int j) {
    return i + j;
}


struct divide {
    int operator()(int denominator, int divisor){
        return denominator / divisor;
    }  
};


int main(){

    auto mod = [](int x, int y){
        return x % y;  
    };


    map<string, function<int(int, int)>> binops = {
        {"+", add},             //函数指针
        {"-", minus<int>()},    //标准库函数对象
        {"/", divide()},        //函数对象
        {"%", mod},             //lambda
        {"*", [](int x, int y){ return x * y; }}    //匿名的lambda
    };    

    cout << "usage: <operator> <int> <int>" << endl;
    cout << "sample: " <<endl;
    cout << "        10 + 5 " << endl;
    cout << "        10 - 5 " << endl;
    cout << "        10 * 5 " << endl;
    cout << "        10 / 5 " << endl;
    cout << "        10 % 5 " << endl;
    cout << endl << endl;

    while (true){
        string op;
        int a, b;
        cin >> a >> op >> b;
        if (!cin){
            cin.clear();
            cin.ignore();
            cout << "input format error, try again!" << endl;
            continue;
        }
        cout << binops[op](a, b) << endl;
    }

    return 0;
}
