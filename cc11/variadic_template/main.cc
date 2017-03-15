
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

int main() {

    // test codes
    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
