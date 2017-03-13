
#include "comm_include.h"

void TestCase1() {  //unique_ptr
    ENTER_FUNC;

    unique_ptr<int> up1(new int(11));
    unique_ptr<int> up2{ new int(12) };
    //unique_ptr<int> up3 = up2;  //unique_ptr不能拷贝构造, 也不能给weak_ptr/shared_ptr引用
    cout << *up1 << endl;
    cout << *up2 << endl;

    unique_ptr<int> up3 = move(up1);
    cout << *up3 << endl;
    //cout << *up1 << endl;   //up1已不再引用有效内存, 会报错
    up1.reset();    //允许对已无效的指针调用
    up1.reset();    //允许重复调用

    up3.reset();
    //cout << *up3 << endl;   //up3已不再引用有效内存, 会报错

    EXIT_FUNC;
}

static void CheckSharedPtr(weak_ptr<int> & wp) {
    shared_ptr<int> sp = wp.lock(); //wp.lock(): 若wp指向的shared_ptr所指向的内存有效, 则返回shared_ptr, 否则返回nullptr
    if (sp != nullptr) {
        cout << "still " << *sp << endl;
    }
    else {
        cout << "pointer is invalid." << endl;
    }
}

void TestCase2() {  //shared_ptr, weak_ptr
    ENTER_FUNC;

    shared_ptr<int> sp1{ new int(22) };
    shared_ptr<int> sp2 = sp1;  
    weak_ptr<int> wp1 = sp1;

    cout << *sp1 << endl;
    cout << *sp2 << endl;
    CheckSharedPtr(wp1);

    *sp1 += 1;  //sp1和sp2指向的是同一块内存, 故修改*sp1等价于修改*sp2
    cout << *sp1 << endl;
    cout << *sp2 << endl;

    sp1.reset();    //指向的内存的引用计数减1
    cout << *sp2 << endl;
    CheckSharedPtr(wp1);

    sp2.reset();
    CheckSharedPtr(wp1);    //直至所指向的内存引用计数减为0, 即不再有shared_ptr引用, weak_ptr才无法转为有效的shared_ptr

    EXIT_FUNC;
}

void TestCase3() {
    ENTER_FUNC;

//#ifndef __GUNC__  //clang also defined __GUNC__
#if defined(__clang__) || defined(_MSC_VER)
    pointer_safety ps = get_pointer_safety();
    switch (ps) {
    case pointer_safety::strict:
        cout << "pointer_safety value: " << (int)ps << ", support minimum GC." << endl;
        break;
    case pointer_safety::preferred:
    case pointer_safety::relaxed:
    default:
        cout << "pointer_safety value: " << (int)ps << ", does not support minimum GC." << endl;
        break;
    }

#endif

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}