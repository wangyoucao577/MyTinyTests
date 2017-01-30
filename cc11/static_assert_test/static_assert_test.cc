
#include <string.h>

// 来自Boost中, 在C++98下通过技巧的一个静态断言实现
#define assert_static_from_boost(e) \
    do { \
        enum {assert_static__ = 1 / (e)}; \
    }while(0)


// 枚举编译器对特性的支持
enum FeaturesSupport {
    C99 = 0x0001,
    ExtInt = 0x0002,
    SAssert = 0x0004,
    NoExpect = 0x0008,
    SMAX = 0x0010,
};

// 检查枚举值定义的静态断言
static_assert((SMAX - 1) == (C99 | ExtInt | SAssert | NoExpect), "Features Support enum define error");

template <typename T, typename U> void bitcopy(T& t, U& u) {

    // 静态断言, 编译时检查参数长度是否相等
    static_assert(sizeof(t) == sizeof(u), "bitcopy function, parameters don't have the same length");
    assert_static_from_boost(sizeof(t) == sizeof(u));

    memcpy(&t, &u, sizeof(u));
}

int main()
{
    assert_static_from_boost(((SMAX - 1) == (C99 | ExtInt | SAssert | NoExpect)));

    int a = 0;
    //double b = 0.1f;
    unsigned int b = 1;
    bitcopy(a, b);
    return 0;
}