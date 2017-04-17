
#include "comm_include.h"

struct HowManyBytes {
    char a;
    int b;
};

void TestCase1() {
    ENTER_FUNC;
    cout << "sizeof(char): " << sizeof(char) << endl;
    cout << "sizeof(int): " << sizeof(int) << endl;
    cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << endl;

    cout << endl;
    cout << "offset of char a: " << offsetof(HowManyBytes, a) << endl;
    cout << "offset of int b: " << offsetof(HowManyBytes, b) << endl;

    EXIT_FUNC;
}

struct ColorVector {
    double r;
    double g;
    double b;
    double a;
};

struct alignas(32) ColorVector32 {
    double r;
    double g;
    double b;
    double a;
};

struct Completed{};

void TestCase2() {
    ENTER_FUNC;
    cout << "alignof(ColorVector): " << alignof(ColorVector) << endl;
    cout << "sizeof(ColorVector): " << sizeof(ColorVector) << endl;

    cout << "alignof(ColorVector32): " << alignof(ColorVector32) << endl;
    cout << "sizeof(ColorVector32): " << sizeof(ColorVector32) << endl;

    cout << "alignof(Completed): " << alignof(Completed) << endl;
    cout << "sizeof(Completed): " << sizeof(Completed) << endl;

    int a;
    long long b;
    auto& c = b;
    char d[1024];
#ifndef _MSC_VER
    //NOTE: VS2015中alignof居然不支持变量作为参数?!
    cout << "alignof(int a): " << alignof(a) << endl;
    cout << "alignof(long long b): " << alignof(b) << endl;
    cout << "alignof(auto& c = b): " << alignof(c) << endl;
    cout << "alignof(char d[1024]): " << alignof(d) << endl;
#endif
    cout << "alignof(int): " << alignof(int) << endl;
    cout << "alignof(long long): " << alignof(long long) << endl;
    cout << "alignof(char [1024]): " << alignof(char[1024]) << endl;

    alignas(double) char e;
    alignas(alignof(double)) char f;
#ifndef _MSC_VER
    cout << "alignof(e): " << alignof(e) << endl;
    cout << "alignof(f): " << alignof(f) << endl;
#endif // _MSC_VER

#ifdef _MSC_VER
    //G++ 4.9版本貌似才有了
    cout << "alignof(std::max_align_t): " << alignof(std::max_align_t) << endl;
#endif
    EXIT_FUNC;
}

#if !defined(__clang__)
//固定容量的数组
template <typename T>
class FixedCapacityArray {
public:
    void push_back(T t) {
        //在data中加入t变量
    }
    //...
    char alignas(T) data[1024] = { 0 }; //实验结果: 在G++上alignas(T)被忽略了, 在vs2015上无法查看变量的对齐, 在mac上clang++编译不过
};

void TestCase3() {
    ENTER_FUNC;
    FixedCapacityArray <char> arrCh;
    cout << "alignof(char): " << alignof(char) << endl;
    cout << "alignof(FixedCapacityArray <char>): " << alignof(FixedCapacityArray <char>) << endl;
#ifndef _MSC_VER
    cout << "alignof(arrCh): " << alignof(arrCh) << endl;
    cout << "alignof(arrCh.data): " << alignof(arrCh.data) << endl;
#endif
    
    FixedCapacityArray <ColorVector32> arrCV;
    cout << "alignof(ColorVector32): " << alignof(ColorVector32) << endl;
    cout << "alignof(FixedCapacityArray <ColorVector32>): " << alignof(FixedCapacityArray <ColorVector32>) << endl;
#ifndef _MSC_VER
    cout << "alignof(arrCV): " << alignof(arrCV) << endl;
    cout << "alignof(arrCV.data): " << alignof(arrCV.data) << endl;
#endif

    EXIT_FUNC;
}
#endif

int main() {

    // test codes
    TestCase1();
    TestCase2();
#if !defined(__clang__)
    TestCase3();
#endif
    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
