
#include "comm_include.h"
#include "TestCase4.h"

atomic_llong total{ 0 };

void func(int) {
    for (long long i = 0; i < 100000000LL; ++i)
    {
        total += i;
    }
}

void TestCase1() {
    ENTER_FUNC;

    thread t1(func, 0);
    thread t2(func, 0);

    t1.join();
    t2.join();
    cout << total << endl;

    EXIT_FUNC;
}

void TestCase2() {
    ENTER_FUNC;

#ifndef _MSC_VER
    //Linux上并未定义此类型, 自己命下别名. 以下两种是等价的
    //using atomic_uint64_t = atomic_ullong;
    using atomic_uint64_t = atomic<uint64_t>;
#endif

    atomic_uint64_t aui64{ 20ULL };
    //atomic_uint64_t aui64_2{ aui64 };   //原子类型不能拷贝赋值

    uint64_t ui64 = aui64;  //可以取值赋给基本类型

    EXIT_FUNC;
}


atomic_flag flock = ATOMIC_FLAG_INIT;

void f(int n) {
    while (flock.test_and_set(memory_order_acquire)) {
        cout << "Waiting from thread " << n << endl;
    }
    cout << "Thread " << n << " starts working" << endl;
}

void g(int n) {
    cout << "Thread " << n << " is going to start." << endl;
    flock.clear();
    cout << "Thread " << n << " starts working" << endl;
}

void TestCase3() {
    long flock_init = flock.test_and_set();   //置true
    cout << "ATOMIC_FLAG_INIT " << flock_init << endl;
    thread t1(f, 1);
    this_thread::sleep_for(std::chrono::milliseconds(5));
    thread t2(g, 2);

    t1.join();
    t2.join();
}

int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}