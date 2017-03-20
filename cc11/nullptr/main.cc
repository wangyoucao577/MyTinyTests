
#include "comm_include.h"

void f(char* c) {
    cout << "invoke f(char*)" << endl;
}
void f(int i) {
    cout << "invoke f(int)" << endl;
}

void TestCase1() {
    ENTER_FUNC;

    f(0);
    //f(NULL);  //vs2015上调用的是f(int), G++编译不过
    f((char*)0);
    f(nullptr);

    EXIT_FUNC;
}

void TestCase2() {
    ENTER_FUNC;

    //nullptr 可以隐式转换为char*
    char* cp = nullptr;

    //不可转换为非指针类型
    //int n1 = nullptr;
#if defined(_MSC_VER)
    //vs2015支持强制转换, 值为0
    int n2 = reinterpret_cast<int>(nullptr);
    int n3 = (int)nullptr;
#endif

#if !defined(_MSC_VER)
    nullptr_t nptr;
#else
    nullptr_t nptr = nullptr;   //vs2015上必须要初始化
#endif
    if (nullptr == nptr) {
        cout << "nullptr_t nptr == nullptr" << endl;
    }
    else {
        cout << "nullptr_t nptr != nullptr" << endl;
    }

    if (nptr < nullptr) {
        cout << "nullptr_t nptr < nullptr" << endl;
    }
    else {
        cout << "nullptr_t nptr !< nullptr" << endl;
    }

    if (0 == nullptr){
        cout << "0 == nullptr" << endl;
    }
    else {
        cout << "0 != nullptr" << endl;
    }
    if (nullptr){
        cout << "nullptr is true" << endl;
    }
    else {
        cout << "nullptr is false" << endl;
    }

    //vs2015上貌似就是转换为了int在操作, 可以通过编译
    //nptr += 1;

    cout << "sizeof(nullptr) " << sizeof(nullptr) << endl;
    cout << "typeid(nullptr) " << typeid(nullptr).name() << endl;

    EXIT_FUNC;
}

template<typename T> void g(T* t){
    cout << "g" << endl;
}
template<typename T> void h(T t){
    cout << "h" << endl;
}

void TestCase3() {
    ENTER_FUNC;

    //g(nullptr); //居然不能推导, 不直观
    g((float*)nullptr);
    g((void*)nullptr);

    h(0);
    h(nullptr);
    h((float*)nullptr);

    EXIT_FUNC;
}

static_assert(sizeof(nullptr) == sizeof(void*), "sizeof(nullptr) == sizeof(void*) failed!");

void TestCase4() {
    int *p1 = 0;
    //int *p2 = (void*)0; //C的用法, C++不支持
    int *p3 = nullptr;
}

void TestCase5() {
    ENTER_FUNC;

    nullptr_t my_null = nullptr;
    printf("0x%x\n", &my_null);
    //printf("0x%x\n", &nullptr);   不允许直接取nullptr的地址
    
    //但可以取右值引用的地址, 取到的是右值引用变量的地址
    const nullptr_t && default_nullptr = nullptr;
    const nullptr_t && default_nullptr_2 = nullptr;
    printf("0x%x 0x%x\n", &default_nullptr, &default_nullptr_2);

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