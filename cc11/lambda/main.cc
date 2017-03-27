
#include "comm_include.h"

void TestCase1() {
    ENTER_FUNC;

    int a = 3, b = 4;

    auto var_print = [&] {
        cout << "a = " << a << ", b = " << b << endl;
    };

    auto sum1 = [](int x, int y)->int {return x + y; };
    cout << sum1(a, b) << endl;

    auto sum2 = [&] {return a + b; };
    cout << sum2() << endl;

    auto sum3 = [=, &b] {return a + b; };   //按值传递时, 是定义的时候直接传值 
    a = 5;
    b = 10;
    cout << sum3() << endl;
    var_print();

    auto sum4_plusplus = [=, &b]() {
        b++;
        return a + b;
    };
    cout << sum4_plusplus() << endl;
    var_print();

    auto sum5_plusplus = [=, &b]() mutable {
        a++;    //加mutable可以修改按值捕获变量, 但依然值不会传出. mutable还是应该用在成员函数中
        b++;
        return a + b;
    };
    cout << sum5_plusplus() << endl;

    var_print();

    EXIT_FUNC;
}

int z = 0;
float c = 0.0;
void TestCase2() {
    ENTER_FUNC;
    int x, y = 3;
    float a, b = 4.0;

    int success = 0;
    
    auto validate = [&]() -> bool {
        if ((x == y + z) && (a == b + c)) {
            return 1;
        }
        else {
            return 0;
        }
    };

    success += validate();

    y = 1024;
    b = 1e13;
    success += validate();

    cout << success << endl;
    EXIT_FUNC;
}

void TestCase3() {
    ENTER_FUNC;
    int times = 100;

    int x = 0;
    for (int i = 0; i < times; ++i)
    {
        x += 10;
    }

    const int y = [=] {   //与x完全等同的赋值, 定义时直接调用. 但此种赋值可以返回给const. 
        int val = 0;
        for (int i = 0; i < times; ++i)
        {
            val += 10;
        }
        return val;
    }();

    cout << x << ", " << y << endl;
    EXIT_FUNC;
}

void TestCase4() {
    ENTER_FUNC;

    int j = 12;
    auto by_val_lambda = [=] {return j + 1; };  //按值传递, 函数定义时决定捕获值
    auto by_ref_lambda = [&] {return j + 1; };  //按引用传递, 函数调用时决定捕获值

    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    j++;
    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    EXIT_FUNC;
}

void TestCase5() {
    ENTER_FUNC;

    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y) {return x + y; };
    cout << typeid(totalChild).name() << endl;

    typedef int(*allChild)(int, int);
    allChild p = totalChild;    //lambda允许赋值给同样定义的函数指针(lambda不能有捕获)

    decltype(totalChild) p2 = totalChild;   
    //decltype(totalChild) p3 = p;  //但函数指针不能赋值给lambda类型变量


    int val = 5;
    cout << val << endl;

    //默认lambda为const, 不允许修改按值捕获的变量
    //auto const_val_lambda = [=] {val = 3; };
    
    //加上mutable修饰后, 取消了const属性, 但修改的值不会传出
    auto mutable_val_lambda = [=]() mutable { val = 6; };
    mutable_val_lambda();
    cout << val << endl;

    //按引用传递, 可以在内部修改捕获的值, 并传出. const修饰的是引用本身. 
    auto const_ref_lambda = [&] { val = 7; };
    const_ref_lambda();
    cout << val << endl;


    EXIT_FUNC;
}

//有operator()的const仿函数, 可与lambda等价
//仿函数的特点: 可以有初始状态
class _functor {
public:
    int operator() (int x, int y) const { return x + y; }
};

void TestCase6() {
    ENTER_FUNC;

    int a = 3, b = 4;
    _functor f;
    cout << f(a, b) << endl;
    cout << [=] {return a + b; }() << endl;

    EXIT_FUNC;
}

class Tax {
private:
    float rate_;
    int base_;
public:
    Tax(float r, int b): rate_(r), base_(b){}
    float operator()(float money)const { return (money - base_) * rate_; }
};

void TestCase7() {
    ENTER_FUNC;
    Tax high(0.4, 30000);
    Tax middle(0.25, 20000);
    cout << "tax over 3w: " << high(37500) << endl;
    cout << "tax over 2w: " << middle(27500) << endl;

    float rate = 0.4;
    int base = 30000;
    auto tax_lambda = [&](int money) {
        return (money - base) * rate;
    };
    cout << "tax_lambda over 3w: " << tax_lambda(37500) << endl;
    rate = 0.25;
    base = 20000;
    cout << "tax_lambda over 2w: " << tax_lambda(27500) << endl;

    EXIT_FUNC;
}

vector<int> largeNums;
const int kBound = 10;
inline void LargeNumberFunc(int i) {
    if (i > kBound) {
        largeNums.push_back(i);
    }
}

class LNums {
public:
    LNums(int bound) : kBound_ {bound} {}

    void operator () (int i) const {
        if (i > kBound_) {
            largeNums.push_back(i);
        }
    }
private:
    const int kBound_{0};
};

void TestCase8() {
    ENTER_FUNC;

    vector<int> nums;
    for (int i = 0; i < 1000; ++i)
    {
        nums.push_back(rand() % 100);
    }

    largeNums.clear();

    //传统的for循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        LargeNumberFunc(*itr);
    }
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + 函数指针遍历
    for_each(nums.begin(), nums.end(), LargeNumberFunc);
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + 仿函数
    for_each(nums.begin(), nums.end(), LNums(kBound));
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + lambda遍历
    for_each(nums.begin(), nums.end(), [](int i) {
        if (i > kBound) {
            largeNums.push_back(i);
        }
    });
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    EXIT_FUNC;
}

void TestCase9(){
    ENTER_FUNC;

    vector<int> nums;
    for (int i = 0; i < 1000; ++i)
    {
        nums.push_back(rand() % 100);
    }
    const int kVal = 10;

    for (auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        if (*itr == kVal) { 
            cout << "for find val: " << *itr << endl;
            break; 
        }
    }

    auto itr1 = find_if(nums.begin(), nums.end(), bind2nd(equal_to<int>(), kVal));
    if (itr1 == nums.end()) {
        cout << "find_if with bind2nd not found." << endl;
    }
    else {
        cout << "find_if with bind2nd find val: " << *itr1 << endl;
    }

    auto itr2 = find_if(nums.begin(), nums.end(), [kVal](int i) {
        return i == kVal;
    });
    if (itr2 == nums.end()) {
        cout << "find_if with lambda not found." << endl;
    }
    else {
        cout << "find_if with lambda find val: " << *itr2 << endl;
    }

    EXIT_FUNC;
}

void TestCase10() {
    ENTER_FUNC;
    vector<int> nums;
    for (int i = 0; i < 10; ++i)
    {
        nums.push_back(rand() % 100);
    }
    const int kPlusVal = 10;

    auto nums_print = [&nums] {
        for (auto& i : nums)
        {
            cout << i << "\t";
        }
        cout << endl;
    };

    nums_print();

    //传统的for
    for (auto i = nums.begin(); i != nums.end(); ++i)
    {
        *i += kPlusVal;
    }
    nums_print();

    // plus<int>() 仅返回了加法结果, 而没有改变迭代器中的内容
    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), kPlusVal));
    nums_print();

    // transform 会将结果写入到第三个参数的迭代中
    transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), kPlusVal));
    nums_print();

    for_each(nums.begin(), nums.end(), [kPlusVal](int &i) {
        i += kPlusVal;
    });
    nums_print();

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();
    TestCase8();
    TestCase9();
    TestCase10();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}