
#include "comm_include.h"

//变长模板的声明
template <typename... Elements> 
class MyTuple;

//变长模板的递归特化
template <typename Head, typename... Tail>
class MyTuple<Head, Tail...> : private MyTuple<Tail...> {
    Head head;
};
//边界条件
template<> class MyTuple<>{};

//非类型变长模板声明
template <int ... A>
class NonTypeVariadicTemplate;

//非类型变长模板的递归特化
template <int first, int ... last>
class NonTypeVariadicTemplate<first, last...> {
public:
    static const long val = first * NonTypeVariadicTemplate<last...>::val;
};

//边界条件
template<>
class NonTypeVariadicTemplate<> {
public:
    static const long val = 1;
};

void TestCase1() {
    ENTER_FUNC;

    MyTuple<int, char, double> mt;
    NonTypeVariadicTemplate<1, 10, 100> ntvt;
    cout << NonTypeVariadicTemplate<2, 5, 10, 15>::val << endl;

    EXIT_FUNC;
}

//理论上的Printf终止, 即变长参数都用完了
void Printf(const char* s) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            //变长参数都用完了, 但还有格式化字符串在
            assert(false);
            throw runtime_error("invalid format string: missing arguments");
        }
        cout << *s++;
    }
}
template <typename T, typename... Args>
void Printf(const char* s, T val, Args... args) {
    while (*s) {
        if (*s == '%' && *++s != '%') {     //%任意接一个非%的字符, 代表需要取出一个参数输出
            //其实并不需要显式地指定输出类型, 因为变长参数中已经带了
            cout << val;
            return Printf(++s, args...);    //取出下一个参数
        }
        cout << *s++;
    }

    //提供了多余的参数
    assert(false);
    throw runtime_error("extra arguments provided to Printf");
}

void TestCase2() {
    ENTER_FUNC;
    Printf("Hello %_ %_ %% %_\n", string("world"), 10, 5.0f);
    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
