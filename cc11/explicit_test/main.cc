
#include "comm_include.h"

/*********************************************************************************/

struct Rational1 {
    Rational1(int n = 0, int d = 1) : num(n), den(d) {
        cout << __func__ << "(" << num << "/" << den << ")" << endl;
    }

    int num;    // Numerator(被除数)
    int den;    // Denominator(除数)
};

struct Rational2 {
    explicit Rational2(int n = 0, int d = 1) : num(n), den(d) {
        cout << __func__ << "(" << num << "/" << den << ")" << endl;
    }

    int num;    // Numerator(被除数)
    int den;    // Denominator(除数)
};

void Display1(Rational1 ra) {
    cout << "Numerator: " << ra.num << " Denominator: " << ra.den << endl;
}
void Display2(Rational2 ra) {
    cout << "Numerator: " << ra.num << " Denominator: " << ra.den << endl;
}

void TestCase1() {
    ENTER_FUNC;

    Rational1 r1_1 = 11;    //首先调用默认构造函数隐式 从 11->Rational1对象, 再调用拷贝构造函数赋值给 r1_1 对象
    Rational1 r1_2(12);

    //Rational2 r2_1 = 21;    //编译不过, 要求 21 显示构造为 Rational2 对象后才能调用拷贝构造函数
    Rational2 r2_2(22);

    Display1(1);

    //Display2(2);            //编译不过, 要求 2 显示构造为 Rational2 对象后才能调用拷贝构造函数
    Display2(Rational2(2));

    EXIT_FUNC;
}


/*********************************************************************************/

template <typename T>
class Ptr {
public:
    Ptr(T* p) : _p(p) {}
    explicit operator bool() const {
        if (_p != 0)
            return true;
        else
            return false;
    }
private:
    T* _p;
};

void TestCase2() {
    ENTER_FUNC;

    int a = 1;
    Ptr<int> p(&a);

    if (p)
        cout << "Valid pointer." << endl;
    else
        cout << "Invalid pointer." << endl;

    Ptr<double> pd(0);
    //cout << p + pd << endl;   // 无法隐式转换为 bool 类型进行 + 操作
    cout << bool(p) + bool(pd) << endl;
    cout << (bool)p + (bool)pd << endl;
    cout << static_cast<bool>(p) + static_cast<bool>(pd) << endl;

    EXIT_FUNC;
}

/*********************************************************************************/
class ConvertTo {};
class Convertable {
public:
    explicit operator ConvertTo () const { return ConvertTo(); }
};
void Func(ConvertTo ct) {}

void Testcase3() {
    ENTER_FUNC;

    Convertable c;

    ConvertTo ct(c);
    //ConvertTo ct2 = c;    // c不能隐式转换为 ConvertTo 对象去调用拷贝构造函数
    ConvertTo ct3 = static_cast<ConvertTo>(c);
    //Func(c);      // c不能隐式转换为 ConvertTo 对象去调用拷贝构造函数
    Func(static_cast<ConvertTo>(c));
    Func(ConvertTo(c));
    Func((ConvertTo)c);

    EXIT_FUNC;
}
/*********************************************************************************/

int main() {

    // test codes
    TestCase1();
    TestCase2();
    Testcase3();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}