
#include "comm_include.h"

double foo() { return 1.1f; }

struct Str {
    int i;
} str1;

void TestCase1() {
    ENTER_FUNC;

    auto x = 1;
    auto y = foo();
    auto str2 = str1;

    cout << typeid(x).name() << endl;
    cout << typeid(y).name() << endl;
    cout << typeid(str2).name() << endl;

    EXIT_FUNC;
}

void TestCase2() {
    ENTER_FUNC;

    unsigned int a = UINT32_MAX;
    unsigned int b = 1;

    auto c = a + b;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = a+b, type: " << typeid(c).name() << ", value: " << c << endl;

    EXIT_FUNC;
}

template<typename T1, typename T2>
double Sum(T1 & t1, T2 & t2) {
    auto s = t1 + t2;
    cout << "t1 type: " << typeid(t1).name() << ", value: " << t1 << endl;
    cout << "t2 type: " << typeid(t2).name() << ", value: " << t2 << endl;
    cout << "s = t1+t2, type: " << typeid(s).name() << ", value: " << s << endl;
    return s;
}

void TestCase3() {
    ENTER_FUNC;

    int a = 3;
    long b = 4;
    float c = 1.0f, d = 2.3f;
    double e = 1.2f, f = 2.5f;

    auto h = Sum<int, long>(a, b);
    auto i = Sum<float, float>(c, d);
    auto j = Sum<double, double>(e, f);

    cout << (typeid(c) == typeid(d)) << endl;   //float == float
    cout << (typeid(j) == typeid(a)) << endl;   //double != int


    EXIT_FUNC;
}

//C++11中可以更灵活更安全的MAX/MIN
#define CC11_MAX(a, b) ({   \
auto _a = (a); \
auto _b = (b); \
(_a > _b) ? _a : _b; \
})

void TestCase4() {
    ENTER_FUNC;

#if !defined(_MSC_VER)
    //vs2015上虽然可以编译通过这个宏 CC11_MAX, 但却不能调用, 没搞明白什么意思..
    //遗留问题:
    auto max1 = CC11_MAX(3, 4);
    auto max2 = CC11_MAX(3, 4.0f);

    cout << "max1 type: " << typeid(max1).name() << ", value: " << max1 << endl;
    cout << "max2 type: " << typeid(max2).name() << ", value: " << max2 << endl;
#endif

    EXIT_FUNC;
}


static int kBar = 3;
int & bar() { return kBar; }

void TestCase5() {
    ENTER_FUNC;

    int x = 10;
    int *y = &x;

    //指针类型
    auto *a = &x;
    auto b = &x;
    auto c = y;
    auto *d = y;
    cout << "a type: " << typeid(a).name() << ", is_reference: " << is_reference<decltype(a)>::value << ", value: " << a << endl;
    cout << "b type: " << typeid(b).name() << ", is_reference: " << is_reference<decltype(b)>::value << ", value: " << b << endl;
    cout << "c type: " << typeid(c).name() << ", is_reference: " << is_reference<decltype(c)>::value << ", value: " << c << endl;
    cout << "d type: " << typeid(d).name() << ", is_reference: " << is_reference<decltype(d)>::value << ", value: " << d << endl;

    //引用类型
    auto &e = x;
    auto &f = bar();
    cout << "e type: " << typeid(e).name() << ", is_reference: " << is_reference<decltype(e)>::value << ", value: " << e << endl;
    cout << "f type: " << typeid(f).name() << ", is_reference: " << is_reference<decltype(f)>::value << ", value: " << f << endl;

    //cv限制符
    //遗留问题: 如何判断类型是否带有cv限制符? 
    const auto g = foo();
    const auto &h = foo();
    auto i = g;
    auto &j = g;
    auto k = h;
    auto &l = h;
    cout << "g type: " << typeid(g).name() << ", is_reference: " << is_reference<decltype(g)>::value 
        << ", value: " << g << endl;
    cout << "h type: " << typeid(h).name() << ", is_reference: " << is_reference<decltype(h)>::value 
        << ", value: " << h << endl;
    cout << "i type: " << typeid(i).name() << ", is_reference: " << is_reference<decltype(i)>::value 
        << ", value: " << i << endl;
    cout << "j type: " << typeid(j).name() << ", is_reference: " << is_reference<decltype(j)>::value 
        << ", value: " << j << endl;
    cout << "k type: " << typeid(k).name() << ", is_reference: " << is_reference<decltype(k)>::value 
        << ", value: " << k << endl;
    cout << "l type: " << typeid(l).name() << ", is_reference: " << is_reference<decltype(l)>::value 
        << ", value: " << l << endl;


    EXIT_FUNC;
}


int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}