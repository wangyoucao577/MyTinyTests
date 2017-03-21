
#include "comm_include.h"

class TwoCstor {
public:
    TwoCstor() = default;
    TwoCstor(int i) : data_(i){}

    TwoCstor(const TwoCstor&) = delete; //删除
    TwoCstor& operator = (const TwoCstor&);
private:
    int data_;
};
TwoCstor& TwoCstor::operator = (const TwoCstor&) = default; //与声明分开的 显式default

void TestCase1() {
    ENTER_FUNC;

    cout << "is_pod<TwoCstor>::value " << is_pod<TwoCstor>::value << endl;

    TwoCstor a;
    //TwoCstor b(a);    //已删除了拷贝构造

    EXIT_FUNC;
}

class ConvType {
public:
    ConvType(int i) {};
    ConvType(char c) = delete;  //避免隐式类型转换
};
void Func(int i){}
void Func(char c) = delete;

void TestCase2() {
    ENTER_FUNC;
    ConvType a(1);
    //ConvType b('a'); //无法调用已删除的函数. 若不删除, 会隐式转换并调用int版本

    Func(1);
    //Func('a');//无法调用已删除的函数. 若不删除, 会隐式转换并调用int版本

    EXIT_FUNC;
}

class NoHeadAlloc {
public:
    void * operator new(std::size_t) = delete;  //禁止new操作符, 只能栈上分配
};

class NoStackAlloc {
public:
    ~NoStackAlloc() = delete;   //禁止析构, 只能通过placement new初始化

    void Print() { cout << "NoStackAlloc" << endl; }
};

void TestCase3() {
    ENTER_FUNC;

    NoHeadAlloc a;
    //NoHeadAlloc *b = new NoHeadAlloc;

    //删除了析构, 于是不能在栈上使用, 也不能使用new/delete分配(可以用new但不能用delete, 故会内存泄露), 只能placement new安全使用
    //NoStackAlloc c;
    void *p = new void*[sizeof(NoStackAlloc)];
    NoStackAlloc* pN = new (p) NoStackAlloc();
    pN->Print();
    delete [] p;

    NoStackAlloc* d = new NoStackAlloc;
    d->Print();
    //delete d; //不能调用delete, 内存泄露
    

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();


    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}